#include "DoublyLinkedList.h"

#include <iostream>
#include <stdexcept>

// =============================================================================
// Given implementation — review this before working on the TODOs below.
// =============================================================================

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
// ! DISCUSSION: No constructor implementation here — DoublyLinkedList() = default
//   in the header tells the compiler to generate it. The compiler-generated
//   constructor uses the in-class initializers (head_ = nullptr, tail_ = nullptr,
//   size_ = 0) so there is nothing for us to write.
//
// ? SEE DIAGRAM: images/doubly_node_structure.png       — node with prev/data/next fields
// ? SEE DIAGRAM: images/singly_vs_doubly_comparison.png — O(1) vs O(n) trade-offs at a glance
//

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
        std::cout << current->data << " <-> ";
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
//
// ? SEE DIAGRAM: images/push_front_doubly.png — four pointer updates, O(1) prepend
//
// ! DISCUSSION: Inserting at the front requires updating FOUR pointers — two on the new node, two on the list:
//   - new_node->next = old head    (new node points forward to old head)
//   - new_node->prev = nullptr     (new node has nothing behind it)
//   - old_head->prev = new_node    (old head now points back to new node)
//   - head_ = new_node             (list's head pointer moves to new node)
//   - edge case: old_head->prev only applies if the list was non-empty;
//     if the list was empty, skip that step and set tail_ to the new node instead

void DoublyLinkedList::push_front(int value) {
    // TODO: Create a new DoublyNode on the heap with the given value
    //       (next points to current head_, prev is nullptr)

    // TODO: If the list is NOT empty: set head_->prev to point back to the new node

    // TODO: If the list WAS empty: set tail_ to the new node
    //       (the new node is both the head and the tail)

    // TODO: Set head_ to the new node and increment size_
}

// ---------------------------------------------------------------------------
// 2. push_back()
// ---------------------------------------------------------------------------
//
// ? SEE DIAGRAM: images/push_back_doubly.png — O(1) append using tail_
//
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
    // TODO: Create a new DoublyNode on the heap with the given value
    //       (prev points to current tail_, next is nullptr)

    // TODO: If the list is NOT empty: set tail_->next to point forward to the new node

    // TODO: If the list WAS empty: set head_ to the new node
    //       (the new node is both the head and the tail)

    // TODO: Set tail_ to the new node and increment size_
}

// ---------------------------------------------------------------------------
// 3. pop_front()
// ---------------------------------------------------------------------------
//
// ? SEE DIAGRAM: images/pop_front_doubly.png — four pointer updates, O(1) removal
//
// ! DISCUSSION: Removing from the front:
//   - underflow check: if the list is empty, throw — cannot remove from nothing
//   - pointer updates:
//       - temp = head_             (save old head before advancing)
//       - head_ = head_->next      (advance head_ to the next node)
//       - head_->prev = nullptr    (new head has nothing behind it)
//       - delete temp; --size_     (free old head and update count)
//   - edge case: if the new head_ is nullptr, the list is now empty — set tail_ = nullptr too

void DoublyLinkedList::pop_front() {
    if (!head_) {
        throw std::underflow_error("Cannot pop from an empty list");
    }

    // TODO: Save head_ to a temp pointer

    // TODO: Advance head_ to the next node

    // TODO: If the new head_ is NOT nullptr: clear its prev pointer to nullptr
    //       Otherwise (list is now empty): set tail_ = nullptr

    // TODO: Delete the saved old head and decrement size_
}

// ---------------------------------------------------------------------------
// 4. pop_back()
// ---------------------------------------------------------------------------
//
// ? SEE DIAGRAM: images/pop_back_doubly.png — O(1) removal via tail_->prev
//
// ! DISCUSSION: This is the other major payoff of a doubly linked list — O(1) pop_back.
//   - singly linked list (CT8): needed trailing pointer traversal to find second-to-last — O(n)
//   - doubly linked list: tail_->prev points DIRECTLY to the second-to-last node — O(1)
//   - steps:
//       - temp = tail_             (save old tail before retreating)
//       - tail_ = tail_->prev      (retreat tail_ to the previous node)
//       - tail_->next = nullptr    (new tail has nothing after it)
//       - delete temp; --size_     (free old tail and update count)
//   - edge case: if the new tail_ is nullptr, the list is now empty — set head_ = nullptr too

void DoublyLinkedList::pop_back() {
    if (!head_) {
        throw std::underflow_error("Cannot pop from an empty list");
    }

    // TODO: Save tail_ to a temp pointer

    // TODO: Retreat tail_ to the previous node (tail_->prev)

    // TODO: If the new tail_ is NOT nullptr: clear its next pointer to nullptr
    //       Otherwise (list is now empty): set head_ = nullptr

    // TODO: Delete the saved old tail and decrement size_
}
