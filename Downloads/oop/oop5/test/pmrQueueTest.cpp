
#include "memoryResource.h"
#include "pmrQueue.h"
#include <gtest/gtest.h>
#include <string>
#include <memory_resource>

struct ComplexType {
    int id;
    double value;
    std::pmr::string name;

    ComplexType(int i, double v, const std::pmr::string& n)
        : id(i), value(v), name(n) {}
};

TEST(FixedBlockMemoryResourceTest, AllocateAndDeallocate) {
    constexpr std::size_t poolSize = 1024;
    FixedBlockMemoryResource resource(poolSize);

    void* ptr1 = resource.allocate(100, alignof(int));
    void* ptr2 = resource.allocate(200, alignof(double));
    void* ptr3 = resource.allocate(300, alignof(std::max_align_t));

    resource.deallocate(ptr2, 200, alignof(double));
    resource.deallocate(ptr1, 100, alignof(int));
    resource.deallocate(ptr3, 300, alignof(std::max_align_t));

    void* ptr4 = resource.allocate(poolSize, alignof(std::max_align_t));
    EXPECT_NE(ptr4, nullptr);
    resource.deallocate(ptr4, poolSize, alignof(std::max_align_t));
}

TEST(FixedBlockMemoryResourceTest, ExhaustMemory) {
    constexpr std::size_t poolSize = 1024;
    FixedBlockMemoryResource resource(poolSize);

    EXPECT_THROW(resource.allocate(poolSize + 1, alignof(int)), std::bad_alloc);
}

TEST(PMRQueueTest, IntQueueOperations) {
    constexpr std::size_t poolSize = 1024 * 1024;
    FixedBlockMemoryResource resource(poolSize);
    std::pmr::polymorphic_allocator<int> intAlloc(&resource);
    PMRQueue<int, std::pmr::polymorphic_allocator<int>> intQueue(intAlloc);

    EXPECT_TRUE(intQueue.empty());

    intQueue.push(1);
    intQueue.push(2);
    intQueue.push(3);

    EXPECT_FALSE(intQueue.empty());
    EXPECT_EQ(intQueue.front(), 1);

    int expected = 1;
    for (const auto& val : intQueue) {
        EXPECT_EQ(val, expected++);
    }

    intQueue.pop();
    EXPECT_EQ(intQueue.front(), 2);
}

TEST(PMRQueueTest, ComplexTypeQueueOperations) {
    constexpr std::size_t poolSize = 1024 * 1024;
    FixedBlockMemoryResource resource(poolSize);
    std::pmr::polymorphic_allocator<ComplexType> complexAlloc(&resource);
    PMRQueue<ComplexType, std::pmr::polymorphic_allocator<ComplexType>> complexQueue(complexAlloc);

    ComplexType c1(1, 1.1, std::pmr::string("First", &resource));
    ComplexType c2(2, 2.2, std::pmr::string("Second", &resource));
    ComplexType c3(3, 3.3, std::pmr::string("Third", &resource));

    complexQueue.push(c1);
    complexQueue.push(std::move(c2));
    complexQueue.push(c3);

    EXPECT_EQ(complexQueue.front().id, 1);
    EXPECT_EQ(complexQueue.front().value, 1.1);
    EXPECT_EQ(complexQueue.front().name, "First");

    int expectedId = 1;
    double expectedValue = 1.1;
    std::vector<std::string> expectedNames = { "First", "Second", "Third" };
    int index = 0;
    for (const auto& elem : complexQueue) {
        EXPECT_EQ(elem.id, expectedId++);
        EXPECT_DOUBLE_EQ(elem.value, expectedValue += 1.0);
        EXPECT_EQ(elem.name, expectedNames[index++]);
    }

    complexQueue.pop();
    EXPECT_EQ(complexQueue.front().id, 2);
}

TEST(PMRQueueTest, EmptyQueuePopThrows) {
    constexpr std::size_t poolSize = 1024;
    FixedBlockMemoryResource resource(poolSize);
    std::pmr::polymorphic_allocator<int> intAlloc(&resource);
    PMRQueue<int, std::pmr::polymorphic_allocator<int>> intQueue(intAlloc);

    EXPECT_THROW(intQueue.pop(), std::runtime_error);
}

TEST(PMRQueueTest, ClearQueue) {
    constexpr std::size_t poolSize = 1024 * 1024;
    FixedBlockMemoryResource resource(poolSize);
    std::pmr::polymorphic_allocator<int> intAlloc(&resource);
    PMRQueue<int, std::pmr::polymorphic_allocator<int>> intQueue(intAlloc);

    for (int i = 0; i < 100; ++i) {
        intQueue.push(i);
    }

    intQueue.clear();
    EXPECT_TRUE(intQueue.empty());

    EXPECT_THROW(intQueue.pop(), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
