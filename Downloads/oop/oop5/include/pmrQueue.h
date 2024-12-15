
#ifndef PMR_QUEUE_H
#define PMR_QUEUE_H

#include <memory>
#include <memory_resource>
#include <iterator>
#include <stdexcept>

template <typename T, typename Alloc = std::pmr::polymorphic_allocator<T>>
class PMRQueue {
    struct Node {
        T value;
        Node* next;

        template <typename U>
        Node(U&& val, Node* nxt) : value(std::forward<U>(val)), next(nxt) {}
    };

public:
    using allocator_type = Alloc;
    using value_type = T;

    class forward_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        forward_iterator(Node* ptr = nullptr) : m_ptr(ptr) {}

        forward_iterator& operator++() {
            if (m_ptr) {
                m_ptr = m_ptr->next;
            }
            return *this;
        }

        forward_iterator operator++(int) {
            forward_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        reference operator*() const {
            return m_ptr->value;
        }

        pointer operator->() const {
            return &(m_ptr->value);
        }

        bool operator==(const forward_iterator& other) const {
            return m_ptr == other.m_ptr;
        }

        bool operator!=(const forward_iterator& other) const {
            return m_ptr != other.m_ptr;
        }

    private:
        Node* m_ptr;
    };

    PMRQueue(const Alloc& alloc = Alloc())
        : m_alloc(alloc), m_head(nullptr), m_tail(nullptr) {}

    ~PMRQueue() {
        clear();
    }

    PMRQueue(const PMRQueue&) = delete;
    PMRQueue& operator=(const PMRQueue&) = delete;

    PMRQueue(PMRQueue&& other) noexcept
        : m_alloc(std::move(other.m_alloc)),
          m_head(other.m_head),
          m_tail(other.m_tail)
    {
        other.m_head = nullptr;
        other.m_tail = nullptr;
    }

    PMRQueue& operator=(PMRQueue&& other) noexcept {
        if (this != &other) {
            clear();
            m_alloc = std::move(other.m_alloc);
            m_head = other.m_head;
            m_tail = other.m_tail;
            other.m_head = nullptr;
            other.m_tail = nullptr;
        }
        return *this;
    }

    void push(const T& value) {
        Node* newNode = allocateNode(value);
        if (m_tail) {
            m_tail->next = newNode;
            m_tail = newNode;
        }
        else {
            m_head = m_tail = newNode;
        }
    }

    void push(T&& value) {
        Node* newNode = allocateNode(std::move(value));
        if (m_tail) {
            m_tail->next = newNode;
            m_tail = newNode;
        }
        else {
            m_head = m_tail = newNode;
        }
    }

    bool empty() const {
        return m_head == nullptr;
    }

    void pop() {
        if (m_head) {
            Node* oldHead = m_head;
            m_head = oldHead->next;
            if (!m_head) {
                m_tail = nullptr;
            }
            deallocateNode(oldHead);
        }
        else {
            throw std::runtime_error("Cannot pop from an empty queue");
        }
    }

    T& front() {
        if (!m_head) {
            throw std::runtime_error("Queue is empty");
        }
        return m_head->value;
    }

    const T& front() const {
        if (!m_head) {
            throw std::runtime_error("Queue is empty");
        }
        return m_head->value;
    }

    void clear() {
        while (!empty()) {
            pop();
        }
    }

    forward_iterator begin() { return forward_iterator(m_head); }

    forward_iterator end() { return forward_iterator(nullptr); }

    forward_iterator begin() const { return forward_iterator(m_head); }

    forward_iterator end() const { return forward_iterator(nullptr); }

private:
    template <typename U>
    Node* allocateNode(U&& val) {
        using NodeAlloc = typename std::allocator_traits<Alloc>::template rebind_alloc<Node>;
        NodeAlloc nodeAlloc(m_alloc);
        Node* nodePtr = std::allocator_traits<NodeAlloc>::allocate(nodeAlloc, 1);
        try {
            std::allocator_traits<NodeAlloc>::construct(nodeAlloc, nodePtr, std::forward<U>(val), nullptr);
        }
        catch (...) {
            std::allocator_traits<NodeAlloc>::deallocate(nodeAlloc, nodePtr, 1);
            throw;
        }
        return nodePtr;
    }

    void deallocateNode(Node* node) {
        using NodeAlloc = typename std::allocator_traits<Alloc>::template rebind_alloc<Node>;
        NodeAlloc nodeAlloc(m_alloc);
        std::allocator_traits<NodeAlloc>::destroy(nodeAlloc, node);
        std::allocator_traits<NodeAlloc>::deallocate(nodeAlloc, node, 1);
    }

    Alloc m_alloc;
    Node* m_head;
    Node* m_tail;
};

#endif
