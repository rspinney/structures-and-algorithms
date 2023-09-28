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

Merge sort

Average performance O(n*log(n))

1. Consider the array as a sequnce of 2^n sub-arrays
2. Starting with lowest nontrivial length subarray = 2
3. merge the two constituent, already sorted, subarrays (initially of length 1)
   into a single sorted subarray
4. double the sub array length which then deals with two longer sorted subarrays

Can be done recursively through recursive function mergeSort which calls 
mergeSort on the subarrays *then* merges the results

Or can be done iteratively in which we start at subarray length 1 and then merge
and double the sub-array length until we have sorted the whole array

In both we have a merge function. This is easiest with an auxillary data structure,
but can be done in-place. The in-place version influences time complexitiy, however,
so should generally be avoided - it should rather be used for linked lists
*/

#include <iostream>
#include <vector>
#include <queue>
#include "random.hpp"
#include "comparators.hpp"

using namespace structures_and_algorithms::random;
using namespace structures_and_algorithms::comparators;

template<typename T>
void swap(T &a, T &b)
{
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

//merge function - merges two sorted subarrays [start,...,mid], and [mid+1,...,end] 
//arranged as [start,...,mid,mid+1,...,end] into one sorted array
template<typename T,typename func>
void merge(std::vector<T> &data, const size_t start, const size_t mid, const size_t end, const func &compare)
{
    std::vector<T> merged;//placeholder array
    merged.reserve(end-start+1);
    size_t i = start, j = mid+1; //start indices for each subarray
    while ((i<=mid) || (j<=end)){//whilst at least one is in bounds
        if((j>end)||((i<=mid)&&(j<=end)&&(compare(data[i],data[j]))))//pick left array
            merged.emplace_back(std::move(data[i++]));//note post-increment, uses data[i], then i=i+1
        else//pick right array
            merged.emplace_back(std::move(data[j++]));
    }
    for (size_t i=0;i<merged.size();++i) //replace array with merged placeholder
        data[start+i] = std::move(merged[i]);
}

//space efficient - but time inefficient - generally don't use it
//more appropriate for linked list where insertions are O(1)
template<typename T,typename func>
void mergeInPlace(std::vector<T> &data, const size_t start, size_t mid, const size_t end, const func &compare)
{
    size_t i = start, j = mid+1; //start indices for each subarray
    if (compare(data[mid],data[mid+1]))//already merged
        return;
    while ((i<=mid) && (j<=end)){//whilst BOTH are in bounds
        if (compare(data[i],data[j])){ // data[i] is in correct position, increment i
            ++i;
        }
        else{ // we need to move data in j to i and move displaced data one to the righ
            T temp = std::move(data[j]);
            for (size_t k = j; k > i; --k) // <-- here is the complexity cost - another inner loop
                swap(data[k],data[k-1]);
            data[i] = std::move(temp);
            //increment everything one to the right
            ++i;
            ++j;
            ++mid; //the boundary between the sub-arrays needs to be shifted too
        }
    }
}
///////////////// RECURSIVE /////////////////////////

template<typename T,typename func>
void mergeSort(std::vector<T> &data,const size_t low,const size_t high, const func &compare){
    if (low >= high)
        return;
    size_t mid = low+(high-low)/2;
    mergeSort(data,low,mid,compare); //lower half
    mergeSort(data,mid+1,high,compare); // upper half
    merge(data,low,mid,high,compare); // after two lower halfs sorted, merge the two sections
}

//entry point
template<typename T,typename func = decltype(lessThan<T>)>
void mergeSort(std::vector<T> &data,const func compare = lessThan<T>){
    mergeSort(data,0,data.size()-1,compare);
}

///////////////// ITERATIVE ///////////////////////

template<typename T,typename func = decltype(lessThan<T>)>
void mergeSortIterative(std::vector<T> &data, const func compare = lessThan<T>)
{   //not based on stack - need to start at lowest granularity
    size_t partitionLength = 1; //start at smallest sub-array length
    while (partitionLength < data.size()){
        for (size_t index = 0 ; index <data.size(); index = index + 2 * partitionLength){
            size_t left = index;
            size_t mid = std::min(left + partitionLength - 1 , data.size()-1);//min function accounts for non 2^n length arrays
            size_t right = std::min(left + 2*partitionLength - 1 , data.size()-1);
            merge(data,left,mid,right,compare); //merge the subarray
        }
        partitionLength *= 2; //double partition length, 1,2,4,8 and so on
    }
}

template<typename T,typename func = decltype(lessThan<T>)>
bool checkSorted(const std::vector<T> &data,func compare = lessThan<T>)
{
    for (size_t i = 1; i<data.size(); ++i)
        if (compare(data[i],data[i-1]))
            return false;
    return true;
}

int main(/*int argc, char* argv[]*/)
{
    typedef int32_t T;
    const int32_t N = 10;
    const T M = 100;
    RndUniform rnd;
    uint32_t count = 0;
    auto compare = greaterThan<T>;
    while (1){
        std::vector<T> data(N);
        
        for (auto & x: data)
            x = M*rnd();

        std::cout<<"before sort"<<std::endl<<std::endl;
        for (auto & x: data)
            std::cout<<x<<std::endl;

        mergeSortIterative(data,compare);

        std::cout<<std::endl<<"after sort "<<count<<std::endl<<std::endl;
        for (auto & x: data)
            std::cout<<x<<std::endl;
        if (!checkSorted(data,compare))
            break;
        ++count;
    }
    return 0;
}