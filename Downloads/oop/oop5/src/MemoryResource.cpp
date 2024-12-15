#include "MemoryResource.h"
#include <new>
#include <cstdlib>

FixedBlockMemoryResource::FixedBlockMemoryResource(std::size_t totalSize)
    : m_totalSize(totalSize)
{
    m_memory = static_cast<std::byte*>(::operator new(totalSize, std::nothrow));
    if (!m_memory) {
        throw std::bad_alloc();
    }

    m_freeBlocks.emplace_back(FreeBlock{ m_memory, totalSize });
}

FixedBlockMemoryResource::~FixedBlockMemoryResource() {
    ::operator delete(m_memory);
}

void* FixedBlockMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    for (auto it = m_freeBlocks.begin(); it != m_freeBlocks.end(); ++it) {
        std::uintptr_t blockStart = reinterpret_cast<std::uintptr_t>(it->ptr);
        std::uintptr_t alignedStart = align_ptr(blockStart, alignment);
        std::size_t padding = alignedStart - blockStart;

        if (it->size >= bytes + padding) {
            std::byte* userPtr = reinterpret_cast<std::byte*>(alignedStart);
            std::size_t remaining = it->size - (bytes + padding);

            if (padding > 0) {
                it->size = padding;
            }
            else {
                m_freeBlocks.erase(it);
            }

            if (remaining > 0) {
                m_freeBlocks.emplace_back(FreeBlock{ userPtr + bytes, remaining });
            }

            std::sort(m_freeBlocks.begin(), m_freeBlocks.end(),
                [](const FreeBlock& a, const FreeBlock& b) {
                    return a.ptr < b.ptr;
                });

            return static_cast<void*>(userPtr);
        }
    }

    throw std::bad_alloc();
}

void FixedBlockMemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    if (p == nullptr) return;

    std::byte* ptr = static_cast<std::byte*>(p);
    m_freeBlocks.emplace_back(FreeBlock{ ptr, bytes });
    mergeFreeBlocks();
}

bool FixedBlockMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}

std::uintptr_t FixedBlockMemoryResource::align_ptr(std::uintptr_t ptr, std::size_t alignment) {
    std::uintptr_t misalignment = ptr % alignment;
    if (misalignment == 0) {
        return ptr;
    }
    return ptr + (alignment - misalignment);
}

void FixedBlockMemoryResource::mergeFreeBlocks() {
    if (m_freeBlocks.empty()) return;

    std::sort(m_freeBlocks.begin(), m_freeBlocks.end(),
        [](const FreeBlock& a, const FreeBlock& b) {
            return a.ptr < b.ptr;
        });

    std::vector<FreeBlock> merged;
    merged.reserve(m_freeBlocks.size());

    merged.push_back(m_freeBlocks[0]);

    for (size_t i = 1; i < m_freeBlocks.size(); ++i) {
        FreeBlock& last = merged.back();
        FreeBlock& current = m_freeBlocks[i];

        if (last.ptr + last.size == current.ptr) {
            last.size += current.size;
        }
        else {
            merged.push_back(current);
        }
    }

    m_freeBlocks = std::move(merged);
}
