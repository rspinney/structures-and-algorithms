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

Indexed Heap structure (min/max/user defined)

As heap (inherits from it her) but allows O(1) look up of elements in the heap
in addition to the root element through a hashmap.

******This assumes all elements in the heap are unique******

Consequently we have additional functions for setting specific elements and finding 
the index of an element

*/

#ifndef INDEXEDHEAP_H
#define INDEXEDHEAP_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "heap.hpp"
#include "comparators.hpp"

using namespace structures_and_algorithms::comparators;

namespace structures_and_algorithms::structures::heaps{

//Extend Heap class to include an indexing map to keep track of which elements are where in the heap
//ASSUMES NO DUPLICATES AS EACH ELEMENT IS A DISTINCT VERTEX
template<typename T,typename func = decltype(lessThan<T>), typename hasher = std::hash<T> > //T data, func comparison algo, hash algo
class IndexedHeap : public Heap<T,func>
{
    std::unordered_map<T,size_t,hasher> indexMap; //maps data in heap (T), to index in heap (size_t), with optional hashfn type (hasher)
    void fillMap()
    {
        for (size_t i=0; i<this->data.size();++i)
            indexMap[this->data[i]]=i;
    }
    void swap(T &a, T &b)
    {
        T temp = std::move(b);
        b = std::move(a);
        a = std::move(temp);

        size_t i = indexMap[a];//<--- same as base class  + these 4 lines
        size_t j = indexMap[b];
        indexMap[b] = i;
        indexMap[a] = j;
    }
    
public:

    //lambda hash - choosing 7 initial buckets as a random choice - that is the only ctor availiable..
    template<typename VectorT>
    IndexedHeap(hasher &hash_,size_t n_,VectorT &&data_, func compare_ = lessThan<T>):Heap<T,func>(n_,std::forward<VectorT>(data_),compare_),indexMap(7,hash_){fillMap();}
    template<typename VectorT>
    IndexedHeap(hasher &hash_,VectorT &&data_, func compare_ = lessThan<T>):Heap<T,func>(std::forward<VectorT>(data_),compare_),indexMap(7,hash_){fillMap();}
    IndexedHeap(hasher &hash_,size_t n_, func compare_ = lessThan<T>):Heap<T,func>(n_,compare_),indexMap(7,hash_){}
    IndexedHeap(hasher &hash_,func compare_ = lessThan<T>):Heap<T,func>(compare_),indexMap(7,hash_){}
    //functor hash
    template<typename VectorT>
    IndexedHeap(size_t n_,VectorT &&data_, func compare_ = lessThan<T>):Heap<T,func>(n_,std::forward<VectorT>(data_),compare_){fillMap();}
    template<typename VectorT>
    IndexedHeap(VectorT &&data_, func compare_ = lessThan<T>):Heap<T,func>(std::forward<VectorT>(data_),compare_){fillMap();}
    IndexedHeap(size_t n_, func compare_ = lessThan<T>):Heap<T,func>(n_,compare_){}
    IndexedHeap(func compare_ = lessThan<T>):Heap<T,func>(compare_){}

    size_t getIndex(const T &val) //get index of data in underlying array
    {
        return indexMap.at(val);
    }

    template<typename V = T>//default template in case of initialiser lists
    void set(size_t index,V &&val) //set the data in underlying array at index to val
    {
        if (index >= this->data.size())
            return;
        this->data[index] = std::forward<V>(val); // update the value
        indexMap[this->data[index]] = index; //update the hash indexing
        this->sendUp(index);
        this->sendDown(index);
    }

    template<typename V = T> //default template in case of initialiser lists
    void reset(const T &oldVal,V &&newVal) //overwrite the element in data data in underlying array at index to val
    {
        set(indexMap.at(oldVal),std::forward<T>(newVal));
    }

    void removeRoot() //removes front (extremal) element
    {
        if (this->data.size()){
            swap(this->data.front(),this->data.back());
            indexMap.erase(this->data.back()); //<--- same as base class  + this line
            this->data.pop_back();
            this->sendDown(0);
        }
    }
    template<typename V>
    void insert(V &&val)
    {
        this->data.push_back(std::forward<V>(val));
        indexMap[val] = this->data.size()-1; //<--- same as base class  + this line
        this->sendUp(this->data.size()-1);
    }
};

}

#endif /*INDEXEDHEAP_H*/
