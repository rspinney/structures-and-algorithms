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

Bubble sort

Average performance O(n^2) - not an efficient sorting algorithm for real use

1. Loop over end point of a range from end of array to beginning
2. Nested loop from beginning to outer loop value
3. swap neighbours if not in order
4. result is largest in considered range is moved to the end
5. range shrinks until the whole array is sorted

remeber std::swap(a,b) is equivalent to
T temp = std::move(a);
a = std::move(b);
b = std::move(temp);
*/

#include <iostream>
#include <vector>
#include "random.hpp"
#include "comparators.hpp"

using namespace structures_and_algorithms::random;
using namespace structures_and_algorithms::comparators;

template<typename T, typename func = decltype(lessThan<T>)>
void bubbleSort(std::vector<T> &data, const func compare = lessThan<T>)
{
    for (int32_t end = data.size()-1;end>=0;--end)
        for (int32_t i=0;i<end;++i)
            if (compare(data[i+1],data[i]))
                std::swap(data[i],data[i+1]);
}

int main(/*int argc, char* argv[]*/)
{
    typedef int32_t T;
    const int32_t N = 10;
    const T M = 100;
    RndUniform rnd;
    std::vector<T> data(N);
    
    for (auto &x: data)
        x = M*rnd();

    std::cout<<"before sort"<<std::endl;
    for (auto &x: data)
        std::cout<<x<<std::endl;

    bubbleSort(data,std::function(greaterThan<T>));

    std::cout<<"after sort"<<std::endl;
    for (auto & x: data)
        std::cout<<x<<std::endl;

    return 0;
}