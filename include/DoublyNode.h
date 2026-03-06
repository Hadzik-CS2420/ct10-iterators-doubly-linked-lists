#pragma once

struct DoublyNode {
    int data;
    DoublyNode* next;
    DoublyNode* prev;

    // Three-parameter constructor — next and prev default to nullptr.
    // Called via uniform initialization: new DoublyNode{value, next, prev}
    // The {} syntax is equivalent to () — it invokes this constructor.
    DoublyNode(int value, DoublyNode* next = nullptr, DoublyNode* prev = nullptr)
        : data{value}, next{next}, prev{prev} {}
};
