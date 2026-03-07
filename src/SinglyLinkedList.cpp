#include "SinglyLinkedList.h"

#include <iostream>
#include <stdexcept>

// =============================================================================
// Given implementations — review these before working on the TODO sections.
// =============================================================================

// --- Destructor ---

SinglyLinkedList::~SinglyLinkedList() {
    while (head_) {
        auto* temp = head_;
        head_      = head_->next;
        delete temp;
    }
}

// --- Insertion ---

void SinglyLinkedList::push_front(int value) {
    head_ = new Node{value, head_};
    ++size_;
}

void SinglyLinkedList::push_back(int value) {
    auto* node = new Node{value};

    if (!head_) {
        head_ = node;
    } else {
        auto* current = head_;
        while (current->next) {
            current = current->next;
        }
        current->next = node;
    }

    ++size_;
}

// --- Removal ---

void SinglyLinkedList::pop_front() {
    if (!head_) {
        throw std::underflow_error("Cannot pop from an empty list");
    }

    auto* temp = head_;
    head_      = head_->next;
    delete temp;
    --size_;
}

void SinglyLinkedList::pop_back() {
    if (!head_) {
        throw std::underflow_error("Cannot pop from an empty list");
    }

    if (!head_->next) {
        delete head_;
        head_ = nullptr;
        --size_;
        return;
    }

    // ! DISCUSSION: The trailing pointer pattern — O(n) cost.
    //   We must walk the entire list to find the second-to-last node.
    //   CT9's DoublyLinkedList eliminates this traversal with a tail_ pointer.
    auto* previous = head_;
    auto* current  = head_->next;
    while (current->next) {
        previous = current;
        current  = current->next;
    }

    previous->next = nullptr;
    delete current;
    --size_;
}

// --- Search & remove ---

bool SinglyLinkedList::contains(int value) const {
    auto* current = head_;
    while (current) {
        if (current->data == value) return true;
        current = current->next;
    }
    return false;
}

void SinglyLinkedList::remove(int value) {
    if (!head_) return;

    if (head_->data == value) {
        pop_front();
        return;
    }

    auto* previous = head_;
    auto* current  = head_->next;
    while (current) {
        if (current->data == value) {
            previous->next = current->next;
            delete current;
            --size_;
            return;
        }
        previous = current;
        current  = current->next;
    }
}

// --- Utility ---

void SinglyLinkedList::print() const {
    auto* current = head_;
    while (current) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr\n";
}

int  SinglyLinkedList::get_size()  const noexcept { return size_; }
bool SinglyLinkedList::is_empty()  const noexcept { return size_ == 0; }

// =============================================================================
// Iterator — implement the five members below.
// =============================================================================

// ? SEE DIAGRAM: images/iterator_begin_end.png — begin() at head_, end() at nullptr sentinel
// ? SEE DIAGRAM: images/iterator_traversal.png — current_ advancing node by node

// ! DISCUSSION: Why do linked lists need iterators?
//
//   Arrays and vectors support indexing — vec[i] jumps directly to element i
//   in O(1) because elements sit in contiguous memory. Linked lists have no
//   indexing. To reach element i, you must walk from head, following i pointers
//   — that is O(n) every time. A naive loop using a hypothetical get(i) method
//   would re-traverse from head on every call:
//
//     for (int i = 0; i < list.get_size(); ++i)
//         std::cout << list.get(i);  // walks from head EVERY iteration — O(n) each = O(n²) total
//
//   An iterator solves this by remembering where you are. The current_ pointer
//   holds your position in the list, and advancing (++it) is a single step — O(1).
//   A full traversal is O(n) total, not O(n²).
//
//   Iterators also give linked lists the same for-each syntax as vectors:
//     for (int val : myVector) { ... }   // works because vector has begin()/end()
//     for (int val : myList)   { ... }   // works once WE add begin()/end()
//   Same syntax, same interface — regardless of whether the container uses
//   contiguous memory or heap-allocated nodes.

// ! DISCUSSION: An iterator wraps a pointer and gives it a standard interface.
//   The for-each loop (range-based for) calls these five pieces:
//   - begin()     — returns an iterator pointing to the first node
//   - end()       — returns a sentinel iterator (nullptr) marking one past the last
//   - operator!=  — checks whether to continue (has the iterator reached end?)
//   - operator*   — reads (or modifies) the current node's value
//   - operator++  — advances to the next node
//
//   operator*, operator++, and operator!= use operator overloading — giving C++
//   operators custom behavior on a user-defined type. The compiler calls our
//   functions whenever it sees *, ++, or != applied to an Iterator object.
//
//   Equivalent forms — the compiler rewrites range-based for into the explicit version:
//
//   Range-based for:            Explicit iterator form:
//   for (int val : list)        for (auto it = list.begin(); it != list.end(); ++it)
//       std::cout << val;           std::cout << *it;

// ---------------------------------------------------------------------------
// 1. begin()
// ---------------------------------------------------------------------------

// ? for-loop:
//   for (auto it = list.begin(); it != list.end(); ++it)
//                  ^^^^^^^^^^^^

// ! DISCUSSION: begin() returns an iterator starting at head_ (the first node).
//   - if the list is empty, head_ is nullptr — begin() == end(), so the loop body never runs

SinglyLinkedList::Iterator SinglyLinkedList::begin() {
    // TODO: Return an Iterator constructed with head_

    return Iterator{nullptr}; // placeholder — remove this line when done
}

// ---------------------------------------------------------------------------
// 2. end()
// ---------------------------------------------------------------------------

// ? for-loop:
//   for (auto it = list.begin(); it != list.end(); ++it)
//                                      ^^^^^^^^^^

// ! DISCUSSION: end() does NOT point to the last node — it constructs a brand new Iterator{nullptr}.
//   - end() has no connection to any node; it exists only as a comparison target
//   - you cannot use end() to read the last value — it holds no node, only nullptr
//   - the loop works by comparison: when ++it walks past the tail, current_ becomes nullptr;
//     operator!= compares that nullptr against end()'s nullptr — they match, so the loop stops
//   - this "one past the last" convention is used by every STL container (vector, list, map, etc.),
//     so the same range-based for and algorithm syntax works uniformly across all of them
//   - end() is never dereferenced — calling *it when it == end() is undefined behavior

SinglyLinkedList::Iterator SinglyLinkedList::end() {
    // TODO: Return an Iterator constructed with nullptr

    return Iterator{nullptr}; // placeholder — this happens to be correct; make it explicit
}

// ---------------------------------------------------------------------------
// 3. operator!=
// ---------------------------------------------------------------------------

// ? for-loop:
//   for (auto it = list.begin(); it != list.end(); ++it)
//                                ^^^^^^^^^^^^^^^^

// ! DISCUSSION: Operator overloading — != is given a custom meaning on Iterator.
//   - the for-loop checks it != list.end() before each iteration
//   - two iterators are equal when they point to the same node (same address)
//   - end() returns Iterator{nullptr}, so the loop stops when current_ reaches nullptr

bool SinglyLinkedList::Iterator::operator!=(const Iterator& other) const {
    // TODO: Return true if this iterator's current_ differs from other's current_
    //       (Hint: compare current_ with other.current_)

    return false; // placeholder — remove this line when done
}

// ---------------------------------------------------------------------------
// 4. operator*
// ---------------------------------------------------------------------------

// ? for-loop:
//   for (auto it = list.begin(); it != list.end(); ++it)  { *it; }
//                                                             ^^^

// ! DISCUSSION: Operator overloading — * is given a custom meaning on Iterator.
//   - *it returns current_->data (the int stored in the node at this position)
//   - mirrors how *ptr gives access to the value a raw pointer points to
//   - returns int& (reference) so changes go through to the node directly

int& SinglyLinkedList::Iterator::operator*() {
    // TODO: Return a reference to the data field of the current node
    //       (Hint: current_ is a Node* — access its data member)

    return current_->data; // placeholder — replace with your implementation
}

// ---------------------------------------------------------------------------
// 5. operator++
// ---------------------------------------------------------------------------

// ? SEE DIAGRAM: images/for_loop_order_post.png  — for loop execution order with it++ (return value discarded)
// ? SEE DIAGRAM: images/for_loop_order.png        — same loop with ++it; increment runs AFTER the body
// ? SEE DIAGRAM: images/pointer_loop_increment.png — why ++it is preferred: iterator objects can't be optimized like raw pointers

// ? for-loop:
//   for (auto it = list.begin(); it != list.end(); ++it)
//                                                  ^^^^

// ! DISCUSSION: Operator overloading — ++ is given a custom meaning on Iterator.
//   - pre-increment (++it) advances current_ to the next node (current_ = current_->next)
//   - returns Iterator& (*this) so the for-loop can call it naturally
//   - note: post-increment (it++) would be a separate overload that returns a copy before advancing

SinglyLinkedList::Iterator& SinglyLinkedList::Iterator::operator++() {
    // TODO: Advance current_ to the next node
    // TODO: Return *this

    return *this; // placeholder — ensure this is the last line after your implementation
}
