#pragma once

struct DoublyNode {
    int data;
    DoublyNode* next;
    DoublyNode* prev;

    // Three-parameter constructor — next and prev default to nullptr
    DoublyNode(int value, DoublyNode* next = nullptr, DoublyNode* prev = nullptr)
        : data{value}, next{next}, prev{prev} {}
};
