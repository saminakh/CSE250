// ============================================================================ 
// UBList.cpp
// ~~~~~~~~~~
// YOUR NAME
// - implement the UBList interface
// ============================================================================ 

#include <cstddef> // this header defines NULL
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "UBList.h"

using namespace std; // BAD PRACTICE

// ============================================================================ 
// DO NOT MODIFY THIS SECTION
// ============================================================================ 
UBList::UBList(Node* h, size_t n) : head(h), numNodes(n)
{
}

UBList::UBList(const UBList& theOther)
{
    Node* cur;
    head = NULL;
    numNodes = 0;
    Node* ptr = theOther.head;
    while (ptr != NULL) {
        numNodes++;
        if (head == NULL) {
            cur = head = new Node(ptr->key);
        } else {
            cur->next = new Node(ptr->key);
            cur = cur->next;
        }
        ptr = ptr->next;
    }
}

void UBList::swap(UBList& theOther)
{
    std::swap(numNodes, theOther.numNodes);
    std::swap(head, theOther.head);
}

UBList& UBList::operator=(const UBList& theOther)
{
    UBList temp(theOther); // deep copy
    swap(temp);
    return *this;
}

UBList::~UBList() 
{
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

void UBList::insert(int x)
{
    head = new Node(x, head);
    numNodes++;
}

string UBList::toString()
{
    ostringstream oss;
    oss << "[" << numNodes << " NODES] : ";
    Node* ptr = head;
    while (ptr != NULL) {                                                       
        oss << ptr->key << " ";                                                
        ptr = ptr->next;                                                        
    }                                                                           
    return oss.str();
}

bool UBList::isSorted()
{
    for (Node* ptr = head; ptr != NULL && ptr->next != NULL; ptr = ptr->next)
        if (ptr->key > ptr->next->key) 
            return false;
    return true;
}

// ============================================================================ 
// START MODIFYING FROM HERE. DO NOT ADD ANY HELPER FUNCTION, JUST IMPLEMENT
// THE FUNCTIONS THAT HAVE TODO: YOUR CODE GOES HERE IN THEM
// ============================================================================ 
void UBList::merge(UBList& theOther)
{
    if (!this->isSorted() || !theOther.isSorted())
        throw runtime_error("Give give me sorted lists to merge");

    // If UBList is empty
    if(head == NULL){
        swap(theOther);
        Node* temp;
        while (theOther.head != NULL) {
            temp = theOther.head;
            theOther.head = theOther.head->next;
            delete temp;
        }
        return;
    }
    // If the other list is empty
    if(theOther.numNodes == 0){
        Node* temp;
        while (theOther.head != NULL) {
            temp = theOther.head;
            theOther.head = theOther.head->next;
            delete temp;
        }
        return;
    }

    // If the other list has a smaller initial node, swap the lists
    if(theOther.head->key <  head->key){
        swap(theOther);
    }

    Node* ptr = head;
    Node* optr = theOther.head;

    // Continue to traverse UBList until we come across a node in the other list that is smaller
    while(ptr->next != NULL && optr != NULL){

        // Smaller node encountered, swap end portions of list
        if(ptr->next->key > optr->key){
            Node* temp = ptr->next;
            ptr->next = optr;
            optr = temp;
        }
        // Increment ptr
        ptr = ptr->next;
    }

    // Ran out of nodes in UBList, tack on end of other list
    if(ptr->next == NULL){
        ptr->next = optr;
    }

    numNodes = numNodes + theOther.numNodes;
    
    theOther.head = NULL;
    theOther.numNodes = 0;  
}

void UBList::remove(int x)
{
    Node* prev = NULL;
    Node* ptr = head;
    while(ptr != NULL){
        // VALUE FOUND HERE
        if(ptr->key == x){
            numNodes = numNodes - 1;
            if(prev == NULL){ // HEAD NEEDS TO BE REMOVED
                head = head->next;
                prev = NULL;
                ptr = head;
            }else if(ptr->next == NULL){ // TAIL NEEDS TO BE REMOVED
                prev->next = NULL;
                return;
            }
            else{ // MIDDLE NODE NEEDS TO BE REMOVED
                prev->next = ptr->next;
                ptr = ptr->next;
            }
        }
        // VALUE NOT FOUND HERE, INCREMENT
        else if(ptr->next == NULL){
            return;
        }
        else{
            prev = ptr;
            ptr = ptr->next;
        }
    }
    delete ptr;
    delete prev;

}

void UBList::sort()
{
    if(head->next == NULL){
        return;
    }

    UBList theOther = *this;
    Node* ptr = theOther.head;
    ptr->next = NULL;

    head = head->next;

    numNodes = numNodes - 1;
    theOther.numNodes = 1;

    sort();
    merge(theOther);

// HOORAY

}
