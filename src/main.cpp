#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

#include <format>
#include <iostream>

int main() {
    std::cout << "=== Code-Together 9: Iterators & Doubly Linked Lists — Farr's Ice Cream ===\n\n";

    // =========================================================================
    // PART 1 — Iterator: walking the ticket queue
    // =========================================================================

    // ! DISCUSSION: Farr's Ice Cream ticket queue is filling up.
    //   The manager wants to inspect the queue without removing anyone —
    //   just read each ticket number and count orders above a threshold.
    //   We could use print(), but iterators let us add logic while we walk.

    std::cout << "=== Part 1: Iterator — Reading the Ticket Queue ===\n\n";

    SinglyLinkedList tickets;
    tickets.push_back(3001);
    tickets.push_back(3002);
    tickets.push_back(3003);
    tickets.push_back(3004);
    tickets.push_back(3005);

    std::cout << "Ticket queue:  ";
    tickets.print();
    std::cout << "\n";

    // --- Explicit iterator syntax ---

    // ! DISCUSSION: The explicit form shows exactly what the range-based for loop does.
    //   begin() returns an iterator to the first node.
    //   end() returns an iterator to nullptr (one past the last node).
    //   operator++ advances; operator!= checks the loop condition; operator* reads the value.

    std::cout << "--- Walking the queue (explicit iterator) ---\n";

    // TODO: Write a for loop using begin(), end(), ++, and * to print each ticket number.
    //       Format each line as: "  Ticket: 3001"

    std::cout << "\n";

    // --- Range-based for loop ---

    // ! DISCUSSION: The compiler rewrites range-based for into the explicit iterator form.
    //   Once begin(), end(), operator++, operator*, and operator!= are implemented,
    //   range-based for works automatically — no extra code needed.

    std::cout << "--- Counting high-priority orders (range-based for) ---\n";

    int high_priority_count = 0;

    // TODO: Write a range-based for loop over 'tickets'.
    //       If the ticket number is greater than 3002, increment high_priority_count.

    std::cout << std::format("High-priority orders (> 3002): {}\n\n", high_priority_count);

    // ! DISCUSSION: Both loops above do exactly the same thing under the hood.
    //   The range-based for is just cleaner syntax when you don't need the iterator itself.

    // =========================================================================
    // PART 2 — DoublyLinkedList: the drive-through pre-order tracker
    // =========================================================================

    // ! DISCUSSION: Farr's Ice Cream opens a drive-through lane.
    //   Cars pull in at the back and are served from the front.
    //   Occasionally, the LAST car in line changes their mind and leaves.
    //
    //   With the singly linked list, pop_back required a full O(n) traversal
    //   to find the second-to-last node. With a doubly linked list, tail_->prev
    //   gets there instantly — O(1).

    std::cout << "=== Part 2: DoublyLinkedList — Drive-Through Pre-Orders ===\n\n";

    DoublyLinkedList drive_through;

    // --- Cars arrive in the drive-through lane ---

    std::cout << "--- Cars pulling in ---\n";

    // TODO: Push order IDs 4001, 4002, 4003, 4004 to the BACK of drive_through
    //       (cars join the back of the line)

    std::cout << "Drive-through: ";
    drive_through.print();
    std::cout << std::format("Cars in line:  {}\n\n", drive_through.get_size());

    // --- A VIP arrives at the front ---

    std::cout << "--- VIP skips to the front ---\n";
    std::cout << "Order 3999 — VIP customer, added to front of line.\n";

    // TODO: Push order ID 3999 to the FRONT of drive_through

    std::cout << "Drive-through: ";
    drive_through.print();
    std::cout << "\n";

    // --- Cashier serves the front car ---

    std::cout << "--- Front car served ---\n";
    std::cout << "Order 3999 served — removing from front.\n";

    // TODO: Call pop_front() to serve the front car

    std::cout << "Drive-through: ";
    drive_through.print();
    std::cout << "\n";

    // --- Last car changes their mind ---

    std::cout << "--- Last car gives up ---\n";
    std::cout << "Order 4004 — tired of waiting, left the lane.\n";

    // ! DISCUSSION: In CT8, this required trailing pointer traversal — O(n).
    //   Now with tail_->prev, we reach the second-to-last node in ONE step — O(1).

    // TODO: Call pop_back() to remove the last car

    std::cout << "Drive-through: ";
    drive_through.print();
    std::cout << std::format("Cars remaining: {}\n", drive_through.get_size());

    return 0;
}
