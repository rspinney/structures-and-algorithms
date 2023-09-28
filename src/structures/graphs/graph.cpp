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

Graph structure with insertion

*/

#include <iostream>
#include <utility>
#include <vector>
#include "graph.hpp"
#include "random.hpp"

using namespace structures_and_algorithms::structures::graphs;
using namespace structures_and_algorithms::random;

int main(/*int argc, char* argv[]*/)
{

    typedef int32_t T;
    typedef int32_t U;
    int32_t N = 10;
    RndUniform rnd;
    std::vector<std::pair<int32_t,int32_t> > data(20);
    
    for (auto & x: data){
        x.first=N*rnd();
        x.second = x.first;
        while (x.second == x.first)
            x.second=N*rnd();
    }
    
    Graph<T,U> graph(N);
    
    for (const auto & x: data)
        graph.addEdge(x.first,x.second);

    graph.print();

    return 0;
}