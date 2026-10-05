# Code-Together 10: Iterators & Doubly Linked Lists

## Overview

An in-class code-together activity introducing two new concepts that build on the singly linked list from CT7 and CT8. In Part 1, students add a nested **Iterator class** to the existing `SinglyLinkedList` — enabling range-based for loops and standard iterator syntax. In Part 2, students implement a **DoublyLinkedList** with `prev_` and `tail_` pointers, unlocking O(1) push and pop from both ends. The scenario follows Farr's Ice Cream: the manager uses an iterator to inspect the ticket queue, then tracks drive-through orders in a doubly linked list.

> ▶️ **Run the tests yourself.** From the top of this repo:
>
> ```
> python3 tests/scorecard.py
> ```
>
> It builds if it needs to, runs the suite, and prints a scored breakdown that
> matches what the autograder awards. Submit a **screenshot of that output** —
> not a repository URL.

## Learning Objectives

- Explain the **purpose of iterators**: abstract traversal into a reusable interface that enables range-based for loops
- Implement a **nested Iterator class** inside a linked list with `operator*`, `operator++`, and `operator!=`
- Implement `begin()` and `end()` and explain the **nullptr sentinel** pattern
- Describe the **structural difference** between `DoublyNode` (`prev`/`data`/`next`) and `Node` (`data`/`next`)
- Implement `push_back` and `pop_back` on a doubly linked list in **O(1)** using `tail_` and `prev_`
- Explain why doubly linked lists require **four pointer updates** per insertion/removal

## Files

| File | Focus | TODOs |
|---|---|---|
| `SinglyLinkedList.cpp` | Iterator: `operator*`, `operator++`, `operator!=`, `begin()`, `end()` | 5 |
| `DoublyLinkedList.cpp` | `push_front`, `push_back`, `pop_front`, `pop_back` | 10 |
| `main.cpp` | Ticket queue iterator traversal (Part 1) + drive-through doubly linked list (Part 2) | 8 |

## Supporting Files

| File | Purpose |
|---|---|
| `Node.h` | Simple `Node` struct (`int data`, `Node* next`) — same as CT7/CT8 |
| `SinglyLinkedList.h` | All CT7+CT8 methods given; adds nested `Iterator` class declaration |
| `DoublyNode.h` | New `DoublyNode` struct (`int data`, `DoublyNode* next`, `DoublyNode* prev`) |
| `DoublyLinkedList.h` | `DoublyLinkedList` class: `head_`, `tail_`, `size_`; Rule of 5 all deleted |

## Teaching Order

### 1. `SinglyLinkedList.cpp` — Iterator class (5 TODOs)

Review the given implementations (destructor, push/pop, contains, remove) as a quick recap, then move to the iterator section.

1. **operator\* — Dereferencing** — returns a reference to `current_->data`; mirrors raw pointer dereference; explain why returning by reference allows `*it = value`
2. **operator++ — Advancing** — sets `current_` to `current_->next` and returns `*this`; pre-increment returns the updated iterator
3. **operator!= — Loop condition** — compares `current_` with `other.current_`; the range-based for loop calls this before every iteration
4. **begin() — Start sentinel** — returns `Iterator{head_}`; if the list is empty, `head_` is nullptr and `begin() == end()`
5. **end() — Past-the-end sentinel** — returns `Iterator{nullptr}`; represents one position past the last node

### 2. `DoublyLinkedList.cpp` — Doubly linked list operations (10 TODOs)

Walk through the given destructor first — same temp-pointer pattern as CT7/CT8, going forward (ignoring `prev`).

1. **push_front — Insert at head** — four pointer updates: new node links to old head; old head's `prev` points back; if empty, `tail_` is set; `head_` advances
2. **push_back — O(1) append** — four pointer updates: new node's `prev` links to old tail; old tail's `next` points forward; if empty, `head_` is set; `tail_` advances; contrast with CT8's O(n) traversal
3. **pop_front — Remove head** — save old head; advance `head_`; clear new head's `prev`; if now empty, clear `tail_`; delete saved
4. **pop_back — O(1) removal** — save old tail; retreat `tail_` via `prev`; clear new tail's `next`; if now empty, clear `head_`; delete saved; contrast with CT8's trailing pointer traversal

### 3. `main.cpp` — Farr's Ice Cream Scenario (8 TODOs)

1. **Part 1 — Explicit iterator loop** — write a for loop using `begin()`/`end()`/`++`/`*` to print each ticket number
2. **Part 1 — Range-based for** — write a range-based for loop to count tickets above a threshold; discuss how the compiler rewrites it into the explicit form
3. **Part 2 — push_back (×4)** — cars join the drive-through lane; demonstrates O(1) append with `tail_`
4. **Part 2 — push_front** — VIP car added to the front
5. **Part 2 — pop_front** — front car is served
6. **Part 2 — pop_back** — last car gives up; O(1) vs CT8's O(n) trailing pointer

## Key Concepts

- **Iterator pattern**: wraps a pointer in an object with standard operators; once `begin()`, `end()`, `operator++`, `operator*`, and `operator!=` exist, range-based for works automatically
- **nullptr sentinel**: `end()` returns `Iterator{nullptr}`; when `current_` reaches nullptr, the loop stops — same as the traversal condition in `print()`
- **O(1) push_back**: `tail_` points directly to the last node — no traversal needed; contrast with singly linked list's O(n) walk
- **O(1) pop_back**: `tail_->prev` reaches the second-to-last node in one step — no trailing pointer pattern needed
- **Four pointer updates**: every doubly linked list insertion/removal must update both the node's own `prev`/`next` AND the list's `head_`/`tail_` as needed

## Diagrams

PNGs are in `images/`. SVG sources are in `images/svgs/` (for editing).

| Diagram | Referenced In | Shows |
|---|---|---|
| `iterator_begin_end` | `SinglyLinkedList.cpp` | `begin()` pointing to head_, `end()` pointing to nullptr sentinel |
| `iterator_traversal` | `SinglyLinkedList.cpp` | `current_` advancing node by node until it reaches nullptr |
| `doubly_node_structure` | `DoublyLinkedList.cpp` | DoublyNode with `prev` ← `data` → `next` vs Node with only `data` → `next` |
| `push_back_doubly` | `DoublyLinkedList.cpp` | New node attaches to `tail_`; `tail_` advances — O(1) |
| `pop_back_doubly` | `DoublyLinkedList.cpp` | `tail_` retreats via `prev`; no traversal required — O(1) |

## Grading (30 points)

| Category | Points | What is tested |
|---|---|---|
| Build | 2 | Project compiles without errors |
| `operator*` | 3 | Dereferences to the current node's data value |
| `operator++` | 3 | Advances the iterator to the next node |
| `operator!=` | 3 | Correctly compares two iterator positions |
| `begin()` / `end()` | 4 | begin() points to head_; end() is the nullptr sentinel |
| `push_front` | 3 | Inserts at head; updates tail_ when list was empty |
| `push_back` | 4 | O(1) insert at tail using tail_; updates head_ when list was empty |
| `pop_front` | 3 | Removes head; updates tail_ when list becomes empty |
| `pop_back` | 5 | O(1) removal using prev_; updates head_ when list becomes empty |

## Comment Conventions

Uses [Better Comments](https://marketplace.visualstudio.com/items?itemName=OmarRwemi.BetterComments) for VS 2022:

| Prefix | Color | Purpose |
|---|---|---|
| `// !` | Important (red) | `DISCUSSION:` teaching notes for instructor walkthrough |
| `// ?` | Question (blue) | `SEE DIAGRAM:` references to visual aids |
| `// TODO:` | Task (orange) | Student exercises (main branch) |
