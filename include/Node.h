#pragma once

struct Node {
    int data;
    Node* next;

    // Two-parameter constructor — next defaults to nullptr
    Node(int value, Node* next = nullptr)
        : data{value}, next{next} {}
};
