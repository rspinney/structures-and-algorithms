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

Heap sort - take an array- heapify it - extract and remove the extreme element repeatedly in order
to get all the data in order.

Uses functions used in heap management to sort.

We adapt heap so that we consider a dynamical bound n,

1. Heapfy whole data based on opposite to desired sort criteria
2. Swap extreme value with data at position n (this will be towards the end of the sorted data)
3. Reduce n -> n-1
4. SendDown data at root (position 1) to re-heapify
5. loop 2-4 until n = 0
*/

#include <iostream>
#include <vector>
#include "random.hpp"
#include "comparators.hpp"

using namespace structures_and_algorithms::random;
using namespace structures_and_algorithms::comparators;

template<typename T, typename func = decltype(lessThan<T>)>
void sendDown(std::vector<T> &data,size_t i,size_t n,func &compare){
    if (i < n){
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t extreme_index = i;
        if ((left < n) && (!compare(data[left],data[extreme_index])))
            extreme_index = left;
        if ((right < n) && (!compare(data[right],data[extreme_index])))
            extreme_index = right;

        if (extreme_index != i){
            std::swap(data[i],data[extreme_index]);
            sendDown(data,extreme_index,n,compare);
        }
    }
}

template<typename T, typename func = decltype(lessThan<T>)>
void sendDownIterative(std::vector<T> &data,size_t i,size_t n,func &compare)
{
    while (i < n){
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t extreme_index = i;
        if ((left < n) && (!compare(data[left],data[extreme_index])))
            extreme_index = left;
        if ((right < n) && (!compare(data[right],data[extreme_index])))
            extreme_index = right;

        if (extreme_index != i){
            std::swap(data[i],data[extreme_index]);
            i = extreme_index;
        }
        else{
            break;
        }
    }
}

template<typename T, typename func = decltype(lessThan<T>)>
void heapify(std::vector<T> &data,func &compare)
{
    for (int32_t index = data.size()/2 -1;index >=0;--index)
        sendDownIterative(data,index,data.size(),compare);
}

template<typename T, typename func = decltype(lessThan<T>)>
void heapSort(std::vector<T> &data,func compare)
{
    heapify(data,compare);
    for (size_t i=0;i<data.size();++i){
        std::swap(data.front(),data[data.size()-i-1]);
        sendDownIterative(data,0,data.size()-i-1,compare);
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

    std::cout<<"before"<<std::endl<<std::endl;
    for (auto & x: data)
        std::cout<<x<<std::endl;

    heapSort(data,lessThan<T>);

    std::cout<<"after"<<std::endl<<std::endl;
    for (auto & x: data)
        std::cout<<x<<std::endl;

    for (auto & x: data)
        x = M*rnd();

    std::cout<<"before"<<std::endl<<std::endl;
    for (auto & x: data)
        std::cout<<x<<std::endl;

    heapSort(data,greaterThan<T>);

    std::cout<<"after"<<std::endl<<std::endl;
    for (auto & x: data)
        std::cout<<x<<std::endl;

    return 0;
}
