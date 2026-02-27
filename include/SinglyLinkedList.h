#pragma once
#include "Node.h"

class SinglyLinkedList {
public:
    SinglyLinkedList() = default;
    ~SinglyLinkedList();

    // Rule of 5: if we don't plan to implement copy/move, we should
    // explicitly delete them — the compiler-generated defaults would do
    // a shallow copy (two lists sharing the same nodes → double-free).
    SinglyLinkedList(const SinglyLinkedList&)            = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;
    SinglyLinkedList(SinglyLinkedList&&)                 = delete;
    SinglyLinkedList& operator=(SinglyLinkedList&&)      = delete;

    // Insertion
    void push_front(int value);   // O(1) — one step: wire a new node to head
    void push_back(int value);    // O(n) — must walk every node to find the end

    // Removal
    void pop_front();             // O(1) — one step: move head to head->next
    void pop_back();              // O(n) — must walk to the second-to-last node

    // Search & remove by value
    bool contains(int value) const;  // O(n) — may need to check every node
    void remove(int value);          // O(n) — must find the node first, then rewire

    // Accessors
    int  get_size()  const noexcept;
    bool is_empty()  const noexcept;

    // Utility
    void print() const;

    // -------------------------------------------------------------------------
    // Iterator — nested class that walks the list node by node
    //
    // Why a nested class?
    //   - this is the standard C++ convention — STL containers (vector,
    //     list, map) all define their iterators as nested classes
    //   - an Iterator only makes sense in the context of this list,
    //     so we scope it inside the class to show that relationship
    //   - from outside you'd write: SinglyLinkedList::Iterator
    // -------------------------------------------------------------------------
    class Iterator {
    public:
        // 'explicit' prevents the compiler from using this constructor
        // for implicit (automatic) type conversions. Without it, a raw
        // Node* could silently convert into an Iterator by accident.
        explicit Iterator(Node* node) : current_{node} {}

        // Operator overloading — we're giving *, ++, and != custom behavior
        // so our Iterator can be used like a pointer in a range-based for loop.
        int&      operator*();                            // dereference:
                                                         //   - iterator holds a Node* (an address)
                                                         //   - *it gives us the data inside the node, not the address
                                                         //   - int& returns by reference so changes go through to the node:
                                                         //       int& → *it = 42;  // changes node's data at 0x7ff3 directly
                                                         //       int  → *it = 42;  // changes a copy at 0xA210 — node at 0x7ff3 unchanged

        Iterator& operator++();                           // pre-increment:
                                                         //   - advances to the next node
                                                         //   - returns Iterator& (reference to itself) so you can
                                                         //     chain calls or use it naturally in a for loop

        bool      operator!=(const Iterator& other) const; // not-equal comparison:
                                                         //   - checks if two iterators point to the same node
                                                         //   - const Iterator& — reference avoids an unnecessary copy,
                                                         //     const because we only need to look at it, not change it
                                                         //   - a for loop uses this to stop: (it != end()),
                                                         //     where end() is an Iterator pointing to nullptr

    private:
        Node* current_;
    };

    Iterator begin();   // returns an Iterator pointing to the first node (head_)
    Iterator end();     // returns an Iterator pointing past the last node (nullptr sentinel)

private:
    Node* head_ = nullptr;
    int   size_ = 0;
};
