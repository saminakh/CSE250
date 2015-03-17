// ============================================================================ 
// UBHeap.h
// ~~~~~~~~
// YOUR NAME
// - a simple Max Heap class
// - THIS FILE MUST BE USED AS IS, Except for the "YOUR NAME" field above
// ============================================================================ 

#ifndef UBHeap_H_
#define UBHeap_H_

#include <vector>

class UBHeap
{
public:
    /**
     * construct a heap from a given array
     * since this has a default parameter, there's a lurking default
     * constructor in here too
     */
    explicit UBHeap(const std::vector<int>& a = std::vector<int>()); 

    UBHeap& operator=(const UBHeap& theOther); // assignment operator

    std::string toString();      // print all members of the heap
    void push(int);              // insert a new int to the heap
    void pop();                  // remove the max element from the heap
    int top();                   // return but not remove the max element
    bool empty();                // return whether the current heap is empty

private:
    std::vector<int> heap_; // storing the heap using an array
    void heapify();         // heapify the array stored in heap_
    void sink(size_t i);    // sink the node whose index is i
    void floatUp(size_t i); // float the node whose index is i
};

#endif