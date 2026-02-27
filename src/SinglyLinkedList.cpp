#include "SinglyLinkedList.h"

#include <format>
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
        std::cout << std::format("{} -> ", current->data);
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

// ! DISCUSSION: An iterator wraps a pointer and gives it a standard interface.
//   The for-each loop (range-based for) calls these five pieces:
//   - begin()     — get an iterator pointing to the first node
//   - end()       — get a sentinel iterator (nullptr) marking one past the last
//   - operator!=  — check whether to continue (has the iterator reached end?)
//   - operator*   — read (or modify) the current node's value
//   - operator++  — advance to the next node
//
//   Equivalent forms — the compiler rewrites range-based for into the explicit version:
//
//   Range-based for:            Explicit iterator form:
//   for (int val : list)        for (auto it = list.begin(); it != list.end(); ++it)
//       std::cout << val;           std::cout << *it;

// --- operator* ---

// ! DISCUSSION: Dereferencing an iterator gives access to the current node's data.
//   - *it returns current_->data (the int inside the node)
//   - mirrors how *ptr gives access to the value a raw pointer points to
//   - returns int& (by reference) so you can modify the node's data directly

int& SinglyLinkedList::Iterator::operator*() {
    // TODO: Return a reference to the data field of the current node
    //       (Hint: current_ is a Node* — access its data member)

    return current_->data; // placeholder — replace with your implementation
}

// --- operator++ ---

// ! DISCUSSION: Pre-increment (++it) advances the iterator to the next node.
//   It moves current_ forward by one step (current_ = current_->next),
//   then returns a reference to *this so chaining works.

SinglyLinkedList::Iterator& SinglyLinkedList::Iterator::operator++() {
    // TODO: Advance current_ to the next node
    // TODO: Return *this

    return *this; // placeholder — ensure this is the last line after your implementation
}

// --- operator!= ---

// ! DISCUSSION: The for-loop checks it != list.end() before each iteration.
//   Two iterators are equal when they point to the same node (same address).
//   end() returns Iterator{nullptr}, so when current_ reaches nullptr the loop stops.

bool SinglyLinkedList::Iterator::operator!=(const Iterator& other) const {
    // TODO: Return true if this iterator's current_ differs from other's current_
    //       (Hint: compare current_ with other.current_)

    return false; // placeholder — remove this line when done
}

// --- begin() ---

// ! DISCUSSION: begin() creates an iterator starting at the first node.
//   If the list is empty, head_ is nullptr — begin() == end(), so the loop body never runs.

SinglyLinkedList::Iterator SinglyLinkedList::begin() {
    // TODO: Return an Iterator constructed with head_

    return Iterator{nullptr}; // placeholder — remove this line when done
}

// --- end() ---

// ! DISCUSSION: end() returns an iterator pointing one past the last node.
//   For a linked list, "one past the last" is nullptr — what next points to after the tail.

SinglyLinkedList::Iterator SinglyLinkedList::end() {
    // TODO: Return an Iterator constructed with nullptr

    return Iterator{nullptr}; // placeholder — this happens to be correct; make it explicit
}
