// ============================================================================ 
// UBHeap!
// ~~~~~~~~~~
// Samina Khan
// ============================================================================ 

#include <cstddef> 
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>

#include "UBHeap.h"
#include "error_handling.h"


using namespace std; // BAD PRACTICE

UBHeap::UBHeap(const std::vector<int>& a) : heap_(a)
{
    heapify();
}



UBHeap& UBHeap::operator=(const UBHeap& theOther)
{
    heap_ = theOther.heap_;
    return *this;
}

void UBHeap::heapify()
{
    for(int i = heap_.size()/2; i >= 0; i--){
        sink(i);
    }
}

void UBHeap::sink(size_t i){
    size_t left, right, my_pick;
    while((left = 2*i + 1) < heap_.size()){
        right = left + 1;
        my_pick = right >= heap_.size() ? left : heap_[right] > heap_[left] ? right : left;
        if(heap_[i] >=heap_[my_pick]) break;
        swap(heap_[i], heap_[my_pick]);
        i = my_pick;
    }

}

void UBHeap::floatUp(size_t i){
    if(!empty()){
        int j = i;
        while((j-1)/2 >=0){
            if(heap_[(j-1)/2] < heap_[j]){
                swap(heap_[(j-1)/2], heap_[j]);
                j = (j-1)/2;            
            }
            else{
                break;
            }
        }
    }else{
        throw runtime_error(string("Heap is empty"));       
    }

}


string UBHeap::toString()
{
    ostringstream oss;
    vector<int>::iterator it = heap_.begin();
    while (it != heap_.end()) {                                                       
        oss << *it << " ";                                                
        it++;                                                        
    }                                                                           
    return oss.str();
}

void UBHeap::push(int x)
{
    heap_.push_back(x);
    floatUp(heap_.size() - 1);

}

void UBHeap::pop()
{
    if(!empty()){
        swap(heap_[0], heap_[heap_.size()-1]);
        heap_.pop_back();
        sink(0);
    }else{
        throw runtime_error(string("Heap is empty"));
    }

}
int UBHeap::top()
{
    if(!empty()){
        return heap_[0];
    }else{
        throw runtime_error(string("Heap is empty"));
    }

}

bool UBHeap::empty()
{
    if(heap_.size() == 0){
        return true;
    }
    return false;

}

