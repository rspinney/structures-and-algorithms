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

Heap test
*/

#include <iostream>
#include "heap.hpp"
#include "random.hpp"

using namespace structures_and_algorithms::structures::heaps;
using namespace structures_and_algorithms::random;
using namespace structures_and_algorithms::comparators;

int main(/*int argc, char* argv[]*/)
{
    typedef int32_t T;
    typedef decltype(greaterThan<T>) func;
    const int32_t N = 10;
    const T M = 100;
    RndUniform rnd;
    std::vector<T> data(N);
        
    for (auto & x: data)
        x = M*rnd();

    Heap<T,func> heapMax(data,greaterThan<T>);
    Heap<T> heapMin(2,data);
    
    std::cout<<"contents"<<std::endl<<std::endl;
    for (auto & x: data)
        std::cout<<x<<std::endl;

    std::cout<<std::endl<<"inserting values "<<M/4<<" "<<M/2<<" "<<3*M/4<<std::endl;
    heapMin.insert(M/4);
    heapMin.insert(M/2);
    heapMin.insert(3*M/4);
    heapMax.insert(M/4);
    heapMax.insert(M/2);
    heapMax.insert(3*M/4);
    std::cout<<"minheap is a heap: "<<heapMin.checkHeap()<<std::endl;
    std::cout<<"maxheap is a heap: "<<heapMax.checkHeap()<<std::endl;

    std::cout<<std::endl<<"Min heap extreme vals - in order"<<std::endl;
    for (size_t i=0;i<N+3;i++){
        std::cout<<heapMin.getRoot()<<std::endl;
        heapMin.removeRoot();
    }

    std::cout<<std::endl<<"Max heap extreme vals - in order"<<std::endl;
    for (size_t i=0;i<N+3;i++){
        std::cout<<heapMax.getRoot()<<std::endl;
        heapMax.removeRoot();
    }

    return 0;
}
