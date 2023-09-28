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

Quick sort

Average performance O(n*log(n))

1. set up function "partition" operating on [low,high] which moves the last value into the correct position, with
    all values before it with having values less than it, and all above greater than it
    e.g. [2,4,1,3,8,7,5] -> [2,4,1,3,5,8,7]
    The value in the correct position is called the "pivot", here it is 5 in index 4.
2. Call the function on the array before the pivot
    e.g. on [2,4,1,3] (which would give [2,1,3,4] with pivot = 4 in index 2)
3. Call the function on the array after the pivot
    e.g. on [8,7] (which would give [7,8] with pivot = 7 in index 0)
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

template<typename T,typename func>
size_t partition(std::vector<T> &data, const size_t low, const size_t high, const func &compare){

    T pivot = data[high]; //take this value - could be any

    //has to be signed integer in case low = 0
    int64_t pivotIndex = low - 1; //index of the end of the front where "less than" values are moved to

    for (size_t index = low; index < high; ++index){ //no need for index <= j
        if (compare(data[index],pivot)){//(data[index] < pivot){
            pivotIndex++;
            swap(data[index],data[pivotIndex]);
        }
    }

    pivotIndex++; //after increment pivotIndex is precisely correct position for pivot.
    swap(data[high],data[pivotIndex]); //move pivot into its correct position
    return pivotIndex; //return the pivot index
}

///////////////// RECURSIVE /////////////////////////

template<typename T,typename func>
void quickSort(std::vector<T> &data, const size_t low, const size_t high, const func &compare){
    if ((low >= high)||(high >= data.size()))
        return;
    size_t pivotIndex = partition(data,low,high,compare); // rearranges data and causes element at pivotIndex to be in the right place
    quickSort(data,low,pivotIndex-1,compare); //lower remaining half
    quickSort(data,pivotIndex+1,high,compare); // upper remaining hald
}

//entry point
template<typename T,typename func = decltype(lessThan<T>)>
void quickSort(std::vector<T> &data,const func compare = lessThan<T>){
    quickSort(data,0,data.size()-1,compare);
}

///////////////// ITERATIVE ///////////////////////

template<typename T,typename func = decltype(lessThan<T>)>
void quickSortIterative(std::vector<T> &data, const func compare = lessThan<T>){
    std::queue<std::pair<size_t,size_t> > partitions;
    partitions.push({0,data.size()-1});
    while (!partitions.empty()){
        size_t low = partitions.front().first;
        size_t high = partitions.front().second;
        partitions.pop();
         if ((low < high)&&(high < data.size())){
            size_t pivotIndex = partition(data,low,high,compare); // rearranges data and causes element at pivotIndex to be in the right place
            partitions.push({low,pivotIndex-1});
            partitions.push({pivotIndex+1,high});
         }
    }
}

int main(/*int argc, char* argv[]*/)
{
    typedef int32_t T;
    const int32_t N = 10;
    const T M = 100;
    RndUniform rnd;
    std::vector<T> data(N);
    
    for (auto & x: data)
        x = M*rnd();

    std::cout<<"before sort"<<std::endl<<std::endl;
    for (auto & x: data)
        std::cout<<x<<std::endl;

    quickSortIterative(data);

    std::cout<<std::endl<<"after sort"<<std::endl<<std::endl;
    for (auto & x: data)
        std::cout<<x<<std::endl;

    return 0;
}