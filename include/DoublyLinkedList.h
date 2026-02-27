#pragma once
#include "DoublyNode.h"

class DoublyLinkedList {
public:
    DoublyLinkedList() = default;
    ~DoublyLinkedList();

    // Rule of 5: if we don't plan to implement copy/move, we should
    // explicitly delete them — the compiler-generated defaults would do
    // a shallow copy (two lists sharing the same nodes → double-free).
    DoublyLinkedList(const DoublyLinkedList&)            = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
    DoublyLinkedList(DoublyLinkedList&&)                 = delete;
    DoublyLinkedList& operator=(DoublyLinkedList&&)      = delete;

    // Insertion — both O(1) because we track head_ AND tail_
    void push_front(int value);   // O(1) — wire a new node to head
    void push_back(int value);    // O(1) — wire a new node to tail (no walking needed!)

    // Removal — both O(1) because we track head_, tail_, AND prev pointers
    void pop_front();             // O(1) — move head to head->next
    void pop_back();              // O(1) — move tail to tail->prev (no walking needed!)

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
