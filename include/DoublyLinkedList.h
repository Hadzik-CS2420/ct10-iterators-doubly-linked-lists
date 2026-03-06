#pragma once
#include "DoublyNode.h"

class DoublyLinkedList {
public:
    // ! DISCUSSION: = default tells the compiler to generate this constructor.
    //   It uses the in-class initializers on the private members:
    //   - head_ = nullptr  (no first node yet)
    //   - tail_ = nullptr  (no last node yet)
    //   - size_ = 0        (empty list)
    DoublyLinkedList() = default;
    ~DoublyLinkedList();

    // ! DISCUSSION: Rule of 5 — copy and move are explicitly deleted.
    //   - the compiler-generated defaults would do a shallow copy,
    //     leaving two lists pointing to the same nodes
    //   - when either list is destroyed, it frees those nodes —
    //     leaving the other list with dangling pointers (double-free)
    //   - deleting these operations makes that mistake a compile error
    DoublyLinkedList(const DoublyLinkedList&)            = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
    DoublyLinkedList(DoublyLinkedList&&)                 = delete;
    DoublyLinkedList& operator=(DoublyLinkedList&&)      = delete;

    // ! DISCUSSION: Both insertion methods are O(1) because we track both ends.
    //   - push_front: head_ points directly to the front — no traversal needed
    //   - push_back:  tail_ points directly to the back  — no traversal needed
    //   Compare to SinglyLinkedList::push_back which must walk the entire list — O(n)
    void push_front(int value);
    void push_back(int value);

    // ! DISCUSSION: Both removal methods are O(1) because of tail_ and prev pointers.
    //   - pop_front: head_       points directly to the front node
    //   - pop_back:  tail_->prev points directly to the second-to-last node
    //   Compare to SinglyLinkedList::pop_back which must walk the entire list — O(n)
    void pop_front();
    void pop_back();

    // Accessors
    int  get_size()  const noexcept;
    bool is_empty()  const noexcept;

    // Utility
    void print() const;

private:
    DoublyNode* head_ = nullptr;
    DoublyNode* tail_ = nullptr;
    int         size_ = 0;
};
