#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

#include <iostream>

int main() {
    std::cout << "=== Code-Together 9: Iterators & Doubly Linked Lists -- Farr's Ice Cream ===\n\n";

    // =========================================================================
    // PART 1 — Iterator: walking the ticket queue
    // =========================================================================
    //
    // ! DISCUSSION: Farr's Ice Cream ticket queue is filling up.
    //   - the manager wants to inspect the queue without removing anyone
    //   - just read each ticket number and count orders above a threshold
    //   - we could use print(), but iterators let us add logic while we walk

    std::cout << "=== Part 1: Iterator -- Reading the Ticket Queue ===\n\n";

    SinglyLinkedList tickets;
    tickets.push_back(3001);
    tickets.push_back(3002);
    tickets.push_back(3003);
    tickets.push_back(3004);
    tickets.push_back(3005);

    std::cout << "Ticket queue:  ";
    tickets.print();
    std::cout << "\n";

    // ---------------------------------------------------------------------------
    // Explicit iterator syntax
    // ---------------------------------------------------------------------------
    //
    // ! DISCUSSION: The explicit form shows exactly what the range-based for loop does.
    //   - begin()    — returns an iterator to the first node
    //   - end()      — returns an iterator to nullptr (one past the last node)
    //   - operator++ — advances the iterator to the next node
    //   - operator!= — checks whether the loop should continue
    //   - operator*  — reads the value at the current node

    std::cout << "--- Walking the queue (explicit iterator) ---\n";

    // TODO: Write a for loop using begin(), end(), ++, and * to print each ticket number.
    //       Format each line as: "  Ticket: 3001"

    std::cout << "\n";

    // ---------------------------------------------------------------------------
    // Range-based for loop
    // ---------------------------------------------------------------------------
    //
    // ! DISCUSSION: The compiler rewrites range-based for into the explicit iterator form.
    //   - once begin(), end(), operator++, operator*, and operator!= are implemented,
    //     range-based for works automatically — no extra code needed
    //
    // ! DISCUSSION: The manager just called ticket 3002 — all tickets above that are still pending.
    //   - iterating with a condition lets us count without modifying or printing the whole queue
    //   - this is something print() alone can't do
    //
    // ! DISCUSSION: Both loops above do exactly the same thing under the hood.
    //   - the range-based for is just cleaner syntax when you don't need the iterator itself

    std::cout << "--- Counting pending orders (tickets not yet called) ---\n";

    int pending_count = 0;

    // TODO: Write a range-based for loop over 'tickets'.
    //       If the ticket number is greater than 3002, increment pending_count.

    std::cout << "Pending orders (after ticket 3002): " << pending_count << "\n\n";

    // =========================================================================
    // PART 2 — DoublyLinkedList: the drive-through pre-order tracker
    // =========================================================================
    //
    // ? SEE DIAGRAM: images/doubly/singly_vs_doubly_comparison.png — O(1) vs O(n) trade-offs at a glance
    //
    // ! DISCUSSION: Farr's Ice Cream opens a drive-through lane.
    //   - cars pull in at the BACK and are served from the FRONT — this is a QUEUE, not a stack
    //   - queue (FIFO — First In, First Out): new arrivals join the back, front gets served first
    //   - stack (LIFO — Last In, First Out): new arrivals go on top, top gets removed first
    //     (a stack would push and pop from the SAME end — like a stack of plates)
    //   - occasionally the LAST car changes their mind and leaves (pop_back)
    //   - singly linked list: pop_back required a full O(n) traversal to find the second-to-last node
    //   - doubly linked list: tail_->prev gets there instantly — O(1)

    std::cout << "=== Part 2: DoublyLinkedList -- Drive-Through Pre-Orders ===\n\n";

    DoublyLinkedList drive_through;

    // ---------------------------------------------------------------------------
    // Cars arrive in the drive-through lane
    // ---------------------------------------------------------------------------
    //
    // ! DISCUSSION: push_back adds each car to the END of the line.
    //   - 4001 arrives first → front of the line
    //   - 4004 arrives last  → back of the line
    //   - reading left to right: front (head_) ... back (tail_)

    std::cout << "--- Cars pulling in ---\n";

    // TODO: Push order IDs 4001, 4002, 4003, 4004 to the BACK of drive_through
    //       (cars join the back of the line)

    std::cout << "Drive-through: ";
    drive_through.print();
    std::cout << "Cars in line:  " << drive_through.get_size() << "\n\n";

    // ---------------------------------------------------------------------------
    // Curbside pickup moves to the front
    // ---------------------------------------------------------------------------
    //
    // ! DISCUSSION: push_front adds to the FRONT of the line — O(1) using head_.
    //   - order 3999 called ahead; their food is ready and waiting
    //   - they skip the drive-through queue and go straight to the pickup window

    std::cout << "--- Curbside pickup moves to front ---\n";
    std::cout << "Order 3999 -- called ahead, order ready, moved to front of serving queue.\n";

    // TODO: Push order ID 3999 to the FRONT of drive_through
    //       (curbside pickup — called ahead, order is ready)

    std::cout << "Drive-through: ";
    drive_through.print();
    std::cout << "\n";

    // ---------------------------------------------------------------------------
    // Pickup window serves the front car
    // ---------------------------------------------------------------------------

    std::cout << "--- Front car served ---\n";
    std::cout << "Order 3999 served -- curbside pickup complete, removing from front.\n";

    // TODO: Call pop_front() to serve the front car

    std::cout << "Drive-through: ";
    drive_through.print();
    std::cout << "\n";

    // ---------------------------------------------------------------------------
    // Last car changes their mind
    // ---------------------------------------------------------------------------
    //
    // ! DISCUSSION: In CT8, pop_back required trailing pointer traversal — O(n).
    //   - now tail_->prev reaches the second-to-last node in ONE step — O(1)

    std::cout << "--- Last car gives up ---\n";
    std::cout << "Order 4004 -- tired of waiting, left the lane.\n";

    // TODO: Call pop_back() to remove the last car

    std::cout << "Drive-through: ";
    drive_through.print();
    std::cout << "Cars remaining: " << drive_through.get_size() << "\n";

    // =========================================================================
    // PART 3 — DoublyLinkedList Iterator: forward & reverse traversal
    // =========================================================================
    //
    // ! DISCUSSION: The doubly linked list's prev pointers unlock a new capability:
    //   - SinglyLinkedList::Iterator can only move FORWARD (operator++)
    //   - DoublyLinkedList::Iterator can move FORWARD (++) AND BACKWARD (--)
    //   - begin()/end() work exactly like the singly linked list — forward traversal
    //   - rbegin()/rend() start at tail_ and walk backward via prev — reverse traversal

    std::cout << "\n=== Part 3: DoublyLinkedList Iterator -- Reviewing Orders ===\n\n";

    std::cout << "Remaining orders: ";
    drive_through.print();

    // ---------------------------------------------------------------------------
    // Forward iteration: explicit iterator
    // ---------------------------------------------------------------------------
    //
    // ! DISCUSSION: This is the explicit form — you control the iterator directly.
    //   - equivalent range-based for:
    //     for (int val : drive_through) { std::cout << "  Order: " << val << "\n"; }

    std::cout << "\n--- Forward (front to back, explicit iterator) ---\n";

    // TODO: Write a for loop using begin(), end(), and ++it to print each order.
    //       Format each line as: "  Order: 4001"

    // ---------------------------------------------------------------------------
    // Forward iteration: range-based for
    // ---------------------------------------------------------------------------
    //
    // ! DISCUSSION: The compiler rewrites this into the explicit form above.
    //   - once begin() and end() exist, range-based for works automatically
    //   - explicit equivalent:
    //     for (auto it = drive_through.begin(); it != drive_through.end(); ++it)
    //         std::cout << "  Order: " << *it << "\n";

    std::cout << "\n--- Forward (front to back, range-based for) ---\n";

    // TODO: Write a range-based for loop over drive_through to print each order.
    //       Format each line as: "  Order: 4001"

    // ---------------------------------------------------------------------------
    // Reverse iteration: explicit iterator
    // ---------------------------------------------------------------------------
    //
    // ! DISCUSSION: rbegin() returns an Iterator at tail_ (the last node).
    //   - operator-- walks backward via prev; rend() is the nullptr sentinel
    //   - mirror image of the forward loop — same structure, opposite direction
    //   - no range-based for equivalent — the language only calls begin()/end(),
    //     so reverse iteration always requires the explicit form

    std::cout << "\n--- Reverse (back to front) ---\n";

    // TODO: Write a for loop using rbegin(), rend(), and --it to print each order
    //       in REVERSE. Format each line as: "  Order: 4003"

    return 0;
}
