#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include <vector>
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

// Helper: capture DoublyLinkedList::print() output
static std::string captureDoublyPrint(const DoublyLinkedList& list) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    list.print();
    std::cout.rdbuf(oldCout);
    return buffer.str();
}

// ==================== Iterator Tests (13 points) ====================

TEST(IteratorTest, BeginReturnsFirstElement) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    auto it = list.begin();
    // Checked before dereferencing. begin() starts out as Iterator{nullptr}
    // in the starter, and *it on that segfaults -- which kills the whole run
    // and prints no score at all. Failing here instead keeps every other
    // test reportable.
    ASSERT_TRUE(it != list.end())
        << "begin() must return the first node, not end(), for a non-empty list";
    EXPECT_EQ(*it, 10);
}

TEST(IteratorTest, DereferenceAfterIncrement) {
    SinglyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    auto it = list.begin();
    // Checked before dereferencing. begin() starts out as Iterator{nullptr}
    // in the starter, and *it on that segfaults -- which kills the whole run
    // and prints no score at all. Failing here instead keeps every other
    // test reportable.
    ASSERT_TRUE(it != list.end())
        << "begin() must return the first node, not end(), for a non-empty list";
    ++it;
    EXPECT_EQ(*it, 20);
}

TEST(IteratorTest, EndEqualsNullSentinel) {
    SinglyLinkedList list;
    list.push_back(42);
    auto it = list.begin();
    ++it;
    EXPECT_TRUE(it != list.end() == false); // it should equal end()
}

TEST(IteratorTest, EmptyListBeginEqualsEnd) {
    SinglyLinkedList list;
    EXPECT_FALSE(list.begin() != list.end());
}

TEST(IteratorTest, RangeBasedForCollectsAllValues) {
    SinglyLinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    std::vector<int> collected;
    for (int val : list) {
        collected.push_back(val);
    }

    ASSERT_EQ(collected.size(), 3u);
    EXPECT_EQ(collected[0], 1);
    EXPECT_EQ(collected[1], 2);
    EXPECT_EQ(collected[2], 3);
}

TEST(IteratorTest, ExplicitIteratorMatchesRangeBasedFor) {
    SinglyLinkedList list;
    list.push_back(5);
    list.push_back(10);
    list.push_back(15);

    std::vector<int> explicit_vals;
    for (auto it = list.begin(); it != list.end(); ++it) {
        explicit_vals.push_back(*it);
    }

    std::vector<int> rangebased_vals;
    for (int val : list) {
        rangebased_vals.push_back(val);
    }

    EXPECT_EQ(explicit_vals, rangebased_vals);
}

// ==================== DoublyLinkedList: push_front Tests (3 points) ====================

TEST(DoublyLinkedListTest, PushFrontSingleElement) {
    DoublyLinkedList list;
    list.push_front(10);
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_TRUE(captureDoublyPrint(list).find("10") != std::string::npos);
}

TEST(DoublyLinkedListTest, PushFrontMultipleElementsCorrectOrder) {
    DoublyLinkedList list;
    list.push_front(30);
    list.push_front(20);
    list.push_front(10);
    EXPECT_EQ(list.get_size(), 3);
    // Should print: 10 <-> 20 <-> 30 <-> nullptr
    std::string output = captureDoublyPrint(list);
    EXPECT_TRUE(output.find("10") < output.find("20"));
    EXPECT_TRUE(output.find("20") < output.find("30"));
}

// ==================== DoublyLinkedList: push_back Tests (4 points) ====================

TEST(DoublyLinkedListTest, PushBackSingleElement) {
    DoublyLinkedList list;
    list.push_back(42);
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_TRUE(captureDoublyPrint(list).find("42") != std::string::npos);
}

TEST(DoublyLinkedListTest, PushBackMultipleElementsCorrectOrder) {
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    EXPECT_EQ(list.get_size(), 3);
    std::string output = captureDoublyPrint(list);
    EXPECT_TRUE(output.find("10") < output.find("20"));
    EXPECT_TRUE(output.find("20") < output.find("30"));
}

TEST(DoublyLinkedListTest, PushBackAndPushFrontMixed) {
    DoublyLinkedList list;
    list.push_back(20);
    list.push_front(10);
    list.push_back(30);
    EXPECT_EQ(list.get_size(), 3);
    std::string output = captureDoublyPrint(list);
    EXPECT_TRUE(output.find("10") < output.find("20"));
    EXPECT_TRUE(output.find("20") < output.find("30"));
}

// ==================== DoublyLinkedList: pop_front Tests (3 points) ====================

TEST(DoublyLinkedListTest, PopFrontRemovesHead) {
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.pop_front();
    EXPECT_EQ(list.get_size(), 2);
    std::string output = captureDoublyPrint(list);
    EXPECT_TRUE(output.find("10") == std::string::npos);
    EXPECT_TRUE(output.find("20") != std::string::npos);
}

TEST(DoublyLinkedListTest, PopFrontToEmpty) {
    DoublyLinkedList list;
    list.push_back(42);
    list.pop_front();
    EXPECT_TRUE(list.is_empty());
}

TEST(DoublyLinkedListTest, PopFrontThrowsOnEmpty) {
    DoublyLinkedList list;
    EXPECT_THROW(list.pop_front(), std::underflow_error);
}

// ==================== DoublyLinkedList: pop_back Tests (5 points) ====================

TEST(DoublyLinkedListTest, PopBackRemovesTail) {
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.pop_back();
    EXPECT_EQ(list.get_size(), 2);
    std::string output = captureDoublyPrint(list);
    EXPECT_TRUE(output.find("30") == std::string::npos);
    EXPECT_TRUE(output.find("20") != std::string::npos);
}

TEST(DoublyLinkedListTest, PopBackSingleNode) {
    DoublyLinkedList list;
    list.push_back(42);
    list.pop_back();
    EXPECT_TRUE(list.is_empty());
}

TEST(DoublyLinkedListTest, PopBackToEmpty) {
    DoublyLinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.pop_back();
    list.pop_back();
    EXPECT_TRUE(list.is_empty());
}

TEST(DoublyLinkedListTest, PopBackThenPushBack) {
    // Ensures tail_ is correctly maintained after pop_back
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.pop_back();
    list.push_back(30);
    EXPECT_EQ(list.get_size(), 2);
    std::string output = captureDoublyPrint(list);
    EXPECT_TRUE(output.find("30") != std::string::npos);
    EXPECT_TRUE(output.find("20") == std::string::npos);
}

TEST(DoublyLinkedListTest, PopBackThrowsOnEmpty) {
    DoublyLinkedList list;
    EXPECT_THROW(list.pop_back(), std::underflow_error);
}

// ==================== DoublyLinkedList Iterator Tests (5 points) ====================

TEST(DoublyIteratorTest, BeginReturnsFirstElement) {
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    auto it = list.begin();
    // Checked before dereferencing. begin() starts out as Iterator{nullptr}
    // in the starter, and *it on that segfaults -- which kills the whole run
    // and prints no score at all. Failing here instead keeps every other
    // test reportable.
    ASSERT_TRUE(it != list.end())
        << "begin() must return the first node, not end(), for a non-empty list";
    EXPECT_EQ(*it, 10);
}

TEST(DoublyIteratorTest, ForwardIteration) {
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    std::vector<int> collected;
    for (auto it = list.begin(); it != list.end(); ++it) {
        collected.push_back(*it);
    }

    ASSERT_EQ(collected.size(), 3u);
    EXPECT_EQ(collected[0], 10);
    EXPECT_EQ(collected[1], 20);
    EXPECT_EQ(collected[2], 30);
}

TEST(DoublyIteratorTest, RbeginReturnsLastElement) {
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    auto it = list.rbegin();
    // rbegin() starts as Iterator{nullptr} in the starter; dereferencing
    // that segfaults and no score is printed for anything.
    ASSERT_TRUE(it != list.rend())
        << "rbegin() must return the last node, not rend(), for a non-empty list";
    EXPECT_EQ(*it, 20);
}

TEST(DoublyIteratorTest, ReverseIteration) {
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    std::vector<int> collected;
    for (auto it = list.rbegin(); it != list.rend(); --it) {
        collected.push_back(*it);
    }

    ASSERT_EQ(collected.size(), 3u);
    EXPECT_EQ(collected[0], 30);
    EXPECT_EQ(collected[1], 20);
    EXPECT_EQ(collected[2], 10);
}

TEST(DoublyIteratorTest, DecrementFromMiddle) {
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    auto it = list.begin();
    // Same reason as the other dereference guards: a null begin() would
    // segfault here and take the whole run with it.
    ASSERT_TRUE(it != list.end())
        << "begin() must return the first node, not end(), for a non-empty list";
    ++it; // now at 20
    ++it; // now at 30
    --it; // back to 20
    EXPECT_EQ(*it, 20);
}

TEST(DoublyIteratorTest, EmptyListBeginEqualsEnd) {
    DoublyLinkedList list;
    EXPECT_FALSE(list.begin() != list.end());
}
