#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

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

    for (auto it = tickets.begin(); it != tickets.end(); ++it) {
        std::cout << "  Ticket: " << *it << "\n";
    }

    std::cout << "\n";

    // --- Range-based for loop ---

    // ! DISCUSSION: The compiler rewrites range-based for into the explicit iterator form.
    //   Once begin(), end(), operator++, operator*, and operator!= are implemented,
    //   range-based for works automatically — no extra code needed.

    std::cout << "--- Counting high-priority orders (range-based for) ---\n";

    int high_priority_count = 0;

    for (int val : tickets) {
        if (val > 3002) ++high_priority_count;
    }

    std::cout << "High-priority orders (> 3002): " << high_priority_count << "\n\n";

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

    drive_through.push_back(4001);
    drive_through.push_back(4002);
    drive_through.push_back(4003);
    drive_through.push_back(4004);

    std::cout << "Drive-through: ";
    drive_through.print();
    std::cout << "Cars in line:  " << drive_through.get_size() << "\n\n";

    // --- A VIP arrives at the front ---

    std::cout << "--- VIP skips to the front ---\n";
    std::cout << "Order 3999 — VIP customer, added to front of line.\n";

    drive_through.push_front(3999);

    std::cout << "Drive-through: ";
    drive_through.print();
    std::cout << "\n";

    // --- Cashier serves the front car ---

    std::cout << "--- Front car served ---\n";
    std::cout << "Order 3999 served — removing from front.\n";

    drive_through.pop_front();

    std::cout << "Drive-through: ";
    drive_through.print();
    std::cout << "\n";

    // --- Last car changes their mind ---

    std::cout << "--- Last car gives up ---\n";
    std::cout << "Order 4004 — tired of waiting, left the lane.\n";

    // ! DISCUSSION: In CT8, this required trailing pointer traversal — O(n).
    //   Now with tail_->prev, we reach the second-to-last node in ONE step — O(1).

    drive_through.pop_back();

    std::cout << "Drive-through: ";
    drive_through.print();
    std::cout << "Cars remaining: " << drive_through.get_size() << "\n";

    return 0;
}
