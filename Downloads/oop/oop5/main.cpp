
#include "memoryResource.h"
#include "pmrQueue.h"
#include <iostream>
#include <string>
#include <memory_resource>

struct ComplexType {
    int id;
    double value;
    std::pmr::string name;

    ComplexType(int i, double v, const std::pmr::string& n)
        : id(i), value(v), name(n) {}
};

int main() {
    try {
        constexpr std::size_t poolSize = 1024 * 1024;
        FixedBlockMemoryResource resource(poolSize);

        std::pmr::polymorphic_allocator<int> intAlloc(&resource);

        {
            PMRQueue<int, std::pmr::polymorphic_allocator<int>> intQueue(intAlloc);

            intQueue.push(10);
            intQueue.push(20);
            intQueue.push(30);

            std::cout << "Int queue elements: ";
            for (const auto& v : intQueue) {
                std::cout << v << " ";
            }
            std::cout << std::endl;

            intQueue.pop();
            std::cout << "After pop, front = " << intQueue.front() << "\n";
        }

        std::pmr::polymorphic_allocator<ComplexType> complexAlloc(&resource);

        {
            PMRQueue<ComplexType, std::pmr::polymorphic_allocator<ComplexType>> complexQueue(complexAlloc);

            ComplexType c1(1, 1.1, std::pmr::string("One", &resource));
            ComplexType c2(2, 2.2, std::pmr::string("Two", &resource));
            ComplexType c3(3, 3.3, std::pmr::string("Three", &resource));

            complexQueue.push(c1);
            complexQueue.push(std::move(c2));
            complexQueue.push(c3);

            std::cout << "Complex queue elements:\n";
            for (const auto& elem : complexQueue) {
                std::cout << "id=" << elem.id << ", value=" << elem.value << ", name=" << elem.name << "\n";
            }

            complexQueue.pop();
            const ComplexType& frontElem = complexQueue.front();
            std::cout << "After pop, front element: id=" << frontElem.id
                      << ", value=" << frontElem.value
                      << ", name=" << frontElem.name << "\n";
        }
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return 0;
}
