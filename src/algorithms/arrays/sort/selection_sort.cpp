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

Selection sort

Average performance O(n^2) - Not for real world use

1. Loop over array of length n with index i
2. In sub-array [i,n] find smallest/largest element and move to index i
3. i <- i + 1

*/

#include <iostream>
#include <vector>
#include "random.hpp"
#include "comparators.hpp"

using namespace structures_and_algorithms::random;
using namespace structures_and_algorithms::comparators;

template<typename T, typename func = decltype(lessThan<T>)>
void selectionSort(std::vector<T> &data, const func compare = lessThan<T>)
{
    for (size_t i=0; i<data.size(); ++i){
        size_t index = i;
        for (size_t j=i; j<data.size(); ++j){
            if (compare(data[j],data[index]))
                index = j;
        }
        std::swap(data[i],data[index]);
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

    selectionSort(data,greaterThan<T>);

    std::cout<<"after sort"<<std::endl;
    for (auto & x: data)
        std::cout<<x<<std::endl;

    return 0;
}