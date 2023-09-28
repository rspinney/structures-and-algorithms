/*****************************************************************************/
/******************** Copyright (C) 2022, Richard Spinney. *******************/
/*****************************************************************************/
//                                                                           //
//    This program is free software: you can redistribute it and/or modify   //
//    it under the terms of the GNU General Public License as published by   //
//    the Free Software Foundation, either version 3 of the License, or      //
//    (at your option) any later version.                                    //
//                                                                           //
//    This program is distributed in the hope that it will be useful,        //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of         //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                           //
//                                                                           //
//    You should have received a copy of the GNU General Public License      //
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/*

Heap structure (min/max/user defined)

Heaps are binary (or other) tree structures that are (almost) complete 
- i.e. they fill up layer by layer to be almost balanced.

Used to implement priority queues - i.e. to keep smallest/largest element
at the front for when it is needed.

The rule is that children are aways smaller/larger than the parent. 
I.e. the heap implements a partial ordering.

We then store them in an array rather than a tree, but the exponential structure
allows us to do the following

If the branching factor is m, and there is an element at index i, then 
the m children are at indices, m*i + 1, m*i + 2, ... , m*i + m

Similarly for any element at index i, we can find the parent index, p, using
p = floor((i-1)/m)

This allows us to have a non-linear data structure, but still be able to
iterate forwards/backwards without holding pointers.

Since the structure branches exponentially, we can expect operations to scale
as O(log(n)) in most cases

*/

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
#include "comparators.hpp"

using namespace structures_and_algorithms::comparators;

namespace structures_and_algorithms::structures::heaps{


//Heap class
template<typename T,typename func = decltype(lessThan<T>)>//data, sorting criterion - default is minHeap
class Heap{
protected:
    size_t n; //degree of the heap - i.e. number of children per node
    std::vector<T> data;
    func compare; //function type to give partial ordering
    
    //convert the data to a heap
    void heapify()
    {
        if (!data.size())
            return;
        for(int32_t index = data.size()/n - 1; index >= 0; --index)
            sendDown(index);
    }
    
    //make virtual in order to specialise in examples - not a sensible real world performance choice!
    virtual void swap(T &a, T &b)
    {
        T temp = std::move(b);
        b = std::move(a);
        a = std::move(temp);
    }
public:
    template<typename VectorT>
    Heap(size_t n_, VectorT &&data_, func compare_ = lessThan<T>):n(std::min(2,static_cast<int>(n_))),data(std::forward<VectorT>(data_)),compare(compare_)
    {
        heapify();
    }
    template<typename VectorT>
    Heap(VectorT &&data_, func compare_ = lessThan<T>):n(2),data(std::forward<VectorT>(data_)),compare(compare_)
    {
        heapify();
    }
    Heap(size_t n_, func compare_ = lessThan<T>):compare(compare_){} //no data provided
    Heap(func compare_ = lessThan<T>):n(2),compare(compare_){} //no data provided

    bool isEmpty(){
        return (data.size()==0);
    }

    void sendUpRecursive(size_t index)
    {
        if ((index >1)&&(index < data.size())){//for parent index to exist
            size_t parent_index = (index - 1)/n;
            if (compare(data[index],data[parent_index])){
                swap(data[index],data[parent_index]);
                sendUpRecursive(parent_index);
            }
        }
    }

    void sendUp(size_t index)
    {
        while ((index >1)&&(index < data.size())){//for parent index to exist
            size_t parent_index = (index - 1)/n;
            if (compare(data[index],data[parent_index])){
                swap(data[index],data[parent_index]);
                index = parent_index;
            }
            else{
                break;
            }
        }
    }

    void sendDownRecursive(size_t index)
    {
        if (index < data.size()){
            size_t extreme_index = index;
            for (size_t j=1; j<=n; ++j){
                size_t child_index = n * index + j;
                if (child_index < data.size())
                    if (!compare(data[extreme_index],data[child_index]))
                        extreme_index = child_index;
            }
            if (extreme_index != index){
                swap(data[index],data[extreme_index]);
                sendDownRecursive(extreme_index);
            }
        }
    }

    void sendDown(size_t index)
    {
        while (index < data.size()){
            size_t extreme_index = index;
            for (size_t j=1; j<=n; ++j){
                size_t child_index = n * index + j;
                if (child_index < data.size())
                    if (!compare(data[extreme_index],data[child_index]))
                        extreme_index = child_index;
            }
            if (extreme_index != index){
                swap(data[index],data[extreme_index]);
                index = extreme_index;
            }
            else{
                break;
            }
        }
    }

    T& getRoot()
    {
        return data[0];
    }

    //make virtual in order to specialise in examples - not a sensible real world performance choice!
    virtual void removeRoot()
    {
        if (data.size()){
            swap(data.front(),data.back());
            data.pop_back();
            sendDown(0);
        }
    }

    //make virtual in order to specialise in examples - not a sensible real world performance choice!
    virtual void insert(T &&val)
    {
        data.push_back(std::move(val));
        sendUp(data.size()-1);
    }
    //no perfect forwarding here as templates cannot be virtual
    virtual void insert(T &val)
    {
        data.push_back(val);
        sendUp(data.size()-1);
    }

    bool checkHeap(){
        for (size_t index=0; index<data.size();++index){
            for (size_t j=1; j<=n;j++){
                size_t childIndex = n * index + j;
                if (childIndex >= data.size())
                    break;
                if (compare(data[childIndex],data[index]))
                    return false;
            }        
        }
        return true;
    }

    std::vector<T>  getData()
    {
        return data;
    }
};

}

#endif /*HEAP_H*/
