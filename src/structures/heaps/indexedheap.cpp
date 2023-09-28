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

Indexed Heap test
*/

#include <iostream>
#include "indexedheap.hpp"
#include "random.hpp"

using namespace structures_and_algorithms::structures::heaps;
using namespace structures_and_algorithms::random;
using namespace structures_and_algorithms::comparators;


//structure to encapsulate an identifier "indexVal" and a value for ordered "sortVal"
//keep these in the heap
template<typename T,typename U>
struct IndexSortPair
{
    T indexVal;
    U sortVal;    
    bool operator< (const IndexSortPair& A) const { return this->sortVal < A.sortVal;};
    bool operator> (const IndexSortPair& A) const { return this->sortVal > A.sortVal;};
    IndexSortPair(){}
    template<typename V,typename W>
    IndexSortPair(V &&v_, W &&w_):indexVal(std::forward<V>(v_)),sortVal(std::forward<W>(w_)){}
    bool operator==(const IndexSortPair &val)const noexcept{return this->indexVal == val.indexVal;}
    //need == operator for hashtable
};

int main(/*int argc, char* argv[]*/)
{
    typedef int32_t T;
    typedef float U;
    typedef decltype(greaterThan<IndexSortPair<T,U>>) func;
    const int32_t N = 10;
    RndUniform rnd;
    std::vector<IndexSortPair<T,U> > data;

    for (size_t i=0;i<N;++i)
        data.push_back({2*i,rnd()});

    std::cout<<"contents"<<std::endl<<std::endl;
    for (const auto & x: data)
        std::cout<<x.indexVal<<" "<<x.sortVal<<std::endl;


    //different ways to instantiate the heap using different hash objects
    //all the below should work:
    #define DECL 4
    #if DECL == 1
    // lambda version
    auto IndexSortHashFn = [](const IndexSortPair<T,U>& val)->size_t{return std::hash<T>{}(val.indexVal);};
    IndexedHeap<IndexSortPair<T,U>,func,decltype(IndexSortHashFn)> maxHeap(IndexSortHashFn,data,greaterThan<IndexSortPair<T,U>>);
    #elif DECL == 2
    // wrapped lambda version
    auto IndexSortHashFn = [](const IndexSortPair<T,U>& val)->size_t{return std::hash<T>{}(val.indexVal);};
    auto fn = std::function(IndexSortHashFn);
    IndexedHeap<IndexSortPair<T,U>,func,decltype(fn)> maxHeap(fn,data,greaterThan<IndexSortPair<T,U>>);
    #elif DECL == 3
    // functor version - only one where we don't need to pass the actual function
    struct IndexSortHasher{size_t operator()(const IndexSortPair<T,U>& val) const {return std::hash<T>{}(val.indexVal);}};
    IndexedHeap<IndexSortPair<T,U>,func,IndexSortHasher> maxHeap(data,greaterThan<IndexSortPair<T,U>>);
    #else
    // wrapped functor version
    struct IndexSortHasher{size_t operator()(const IndexSortPair<T,U>& val) const {return std::hash<T>{}(val.indexVal);}};
    auto fn = std::function(IndexSortHasher());
    IndexedHeap<IndexSortPair<T,U>,func,decltype(fn)> maxHeap(fn,data,greaterThan<IndexSortPair<T,U>>);
    #endif

    std::cout<<std::endl<<"adjusting value with indexVal 4 to have a sort value of 5"<<std::endl;

    maxHeap.reset({4,0},{4,5}); // the sortvalue for the old value is irrelvant here - just use 0

    std::cout<<"maxheap is a heap: "<<maxHeap.checkHeap()<<std::endl;

    std::cout<<"in order after adjustment"<<std::endl<<std::endl;
    std::cout<<std::endl<<"Max heap extreme vals - in order"<<std::endl;
    while (!maxHeap.isEmpty()){
        std::cout<<maxHeap.getRoot().indexVal<<" "<<maxHeap.getRoot().sortVal<<std::endl;
        maxHeap.removeRoot();
    }

    /*
    //point of comparison with the above - it emulates std::unordered_map behaviour
    //for instance

    struct test{size_t operator()(const int& val) const {return std::hash<int>{}(val);}};
    auto fn1 = std::function(test());
    std::unordered_map<int,float,decltype(fn1)> hm1(7,fn1); // <--- compiles and works
    std::unordered_map<int,float,test> hm2;                 // <--- compiles and works
    std::unordered_map<int,float,decltype(fn1)> hm3;        // <--- compiles and throws std::bad_function_call
    hm1[4] = 4.5f; //<---fine
    hm2[4] = 4.5f; //<---fine
    hm3[4] = 4.5f; //<---throws here
    */

    return 0;
}
