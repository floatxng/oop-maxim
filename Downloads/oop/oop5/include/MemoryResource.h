
#ifndef MEMORY_RESOURCE_H
#define MEMORY_RESOURCE_H

#include <memory_resource>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <cstdint>

class FixedBlockMemoryResource : public std::pmr::memory_resource {
public:
    explicit FixedBlockMemoryResource(std::size_t totalSize);

    ~FixedBlockMemoryResource() override;

    FixedBlockMemoryResource(const FixedBlockMemoryResource&) = delete;
    FixedBlockMemoryResource& operator=(const FixedBlockMemoryResource&) = delete;

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;

    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    struct FreeBlock {
        std::byte* ptr;
        std::size_t size;
    };

    void mergeFreeBlocks();

    static std::uintptr_t align_ptr(std::uintptr_t ptr, std::size_t alignment);

    std::byte* m_memory;
    std::size_t m_totalSize;
    std::vector<FreeBlock> m_freeBlocks;
};

#endif
