#include "DoublyLinkedList.h"

#include <format>
#include <iostream>
#include <stdexcept>

// =============================================================================
// Given implementation — review this before working on the TODOs below.
// =============================================================================

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
// Same temp-pointer pattern as the singly linked list: save head, advance, delete.
// The prev pointers don't matter here — we're freeing every node in forward order.
//
// ! DISCUSSION: Why not delete backwards using tail_?
//   - we could walk tail_ backwards via prev, but forward traversal is simpler and equally correct
//   - the same temp-pointer pattern from CT7 works here too

DoublyLinkedList::~DoublyLinkedList() {
    while (head_) {
        auto* temp = head_;
        head_      = head_->next;
        delete temp;
    }
}

// ---------------------------------------------------------------------------
// Utility
// ---------------------------------------------------------------------------

void DoublyLinkedList::print() const {
    // ! DISCUSSION: Doubly linked lists can be printed in either direction.
    //   Here we go forward (head to tail), same traversal as a singly linked list.
    auto* current = head_;
    while (current) {
        std::cout << std::format("{} <-> ", current->data);
        current = current->next;
    }
    std::cout << "nullptr\n";
}

int  DoublyLinkedList::get_size()  const noexcept { return size_; }
bool DoublyLinkedList::is_empty()  const noexcept { return size_ == 0; }

// =============================================================================
// TODO sections — implement the four methods below.
// =============================================================================

// ---------------------------------------------------------------------------
// 1. push_front()
// ---------------------------------------------------------------------------

// ? SEE DIAGRAM: images/doubly_node_structure.png — node with prev/data/next fields

// ! DISCUSSION: Inserting at the front requires updating FOUR pointers — two on the new node, two on the list:
//   - new_node->next = old head    (new node points forward to old head)
//   - new_node->prev = nullptr     (new node has nothing behind it)
//   - old_head->prev = new_node    (old head now points back to new node)
//   - head_ = new_node             (list's head pointer moves to new node)
//   - edge case: old_head->prev only applies if the list was non-empty;
//     if the list was empty, skip that step and set tail_ to the new node instead

void DoublyLinkedList::push_front(int value) {
    auto* node = new DoublyNode{value, head_, nullptr};

    if (head_) {
        head_->prev = node;
    } else {
        tail_ = node;
    }

    head_ = node;
    ++size_;
}

// ---------------------------------------------------------------------------
// 2. push_back()
// ---------------------------------------------------------------------------

// ? SEE DIAGRAM: images/push_back_doubly.png — O(1) append using tail_

// ! DISCUSSION: This is where tail_ pays off — O(1) instead of O(n).
//   - singly linked list: push_back had to traverse the entire list to find the last node — O(n)
//   - doubly linked list: tail_ points directly to the last node, so we attach in constant time — O(1)
//   - four pointer updates (mirroring push_front, but at the back):
//       - new_node->prev = old tail    (new node points back to old tail)
//       - new_node->next = nullptr     (new node has nothing ahead of it)
//       - old_tail->next = new_node    (old tail now points forward to new node)
//       - tail_ = new_node             (list's tail pointer moves to new node)
//   - edge case: old_tail->next only applies if the list was non-empty;
//     if the list was empty, skip that step and set head_ to the new node instead

void DoublyLinkedList::push_back(int value) {
    auto* node = new DoublyNode{value, nullptr, tail_};

    if (tail_) {
        tail_->next = node;
    } else {
        head_ = node;
    }

    tail_ = node;
    ++size_;
}

// ---------------------------------------------------------------------------
// 3. pop_front()
// ---------------------------------------------------------------------------

// ! DISCUSSION: Removing from the front:
//   - underflow check: if the list is empty, throw — cannot remove from nothing
//   - save old head to a temp pointer, then advance head_ to head_->next
//   - if the new head_ is NOT nullptr: clear head_->prev = nullptr (nothing behind it now)
//   - if the new head_ IS nullptr: the list is now empty — set tail_ = nullptr too
//   - delete the saved old head and decrement size_

void DoublyLinkedList::pop_front() {
    if (!head_) {
        throw std::underflow_error("Cannot pop from an empty list");
    }

    auto* temp = head_;
    head_      = head_->next;

    if (head_) {
        head_->prev = nullptr;
    } else {
        tail_ = nullptr;
    }

    delete temp;
    --size_;
}

// ---------------------------------------------------------------------------
// 4. pop_back()
// ---------------------------------------------------------------------------

// ? SEE DIAGRAM: images/pop_back_doubly.png — O(1) removal via tail_->prev

// ! DISCUSSION: This is the other major payoff of a doubly linked list — O(1) pop_back.
//   - singly linked list (CT8): needed trailing pointer traversal to find second-to-last — O(n)
//   - doubly linked list: tail_->prev points DIRECTLY to the second-to-last node — O(1)
//   - steps:
//       - save tail_ to a temp pointer
//       - retreat tail_ to tail_->prev
//       - if the new tail_ is NOT nullptr: clear tail_->next = nullptr (nothing after it now)
//       - if the new tail_ IS nullptr: the list is now empty — set head_ = nullptr too
//       - delete the saved old tail and decrement size_

void DoublyLinkedList::pop_back() {
    if (!head_) {
        throw std::underflow_error("Cannot pop from an empty list");
    }

    auto* temp = tail_;
    tail_      = tail_->prev;

    if (tail_) {
        tail_->next = nullptr;
    } else {
        head_ = nullptr;
    }

    delete temp;
    --size_;
}
