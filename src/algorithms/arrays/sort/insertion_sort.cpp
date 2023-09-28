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

Insertion sort

Average performance O(n^2)

1. Loop over array
2. With each value move it to the correct place in the array in front of it
3. This necessitates "shifting" the whole array between its original position and new position "up one" place

We do this by looping
i: 1 -> n-1
store value to be inserted val = data[i]
Then loop j: i-1 -> 0
while looking at bigger values than "val" move every element up one: data[j+1]=data[j]
Then insert the value in the place where you end up
data[j+1] = val
*/

#include <iostream>
#include <vector>
#include "random.hpp"
#include "comparators.hpp"

using namespace structures_and_algorithms::random;
using namespace structures_and_algorithms::comparators;

template<typename T, typename func = decltype(lessThan<T>)>
void insertionSort(std::vector<T> &data, const func compare = lessThan<T>)
{
    for (size_t i=1; i<data.size(); ++i){
        int32_t val = data[i];
        int32_t j = i - 1;
        while ((j >= 0 )&& (compare(val,data[j]))){ //move all the values up one if greater than the value
            data[j+1]=data[j];
            --j;
        }
        data[j+1] = val;
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

    std::cout<<"before sort"<<std::endl;
    for (auto & x: data)
        std::cout<<x<<std::endl;

    insertionSort(data);

    std::cout<<"after sort"<<std::endl;
    for (auto & x: data)
        std::cout<<x<<std::endl;

    return 0;
}