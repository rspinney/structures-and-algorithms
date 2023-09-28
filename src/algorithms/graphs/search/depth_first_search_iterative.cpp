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

Depth First Search for a graph - Iterative

Input: Graph, key
Output: boolean found/not found

Time: O(log(V))
Space: O(log(V))

We visit a node and add its neighbours to a stack of nodes to search
To eliminate loops we record a visitation history to each node - only search neighbours 
if previously unvisited

Notes: general concerns about recursion - space complexity due to number of stack frames

*/

#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include "graph.hpp"
#include "random.hpp"

using namespace structures_and_algorithms::structures::graphs;
using namespace structures_and_algorithms::random;

template<typename T,typename U>
class GraphDFSI : public Graph<T,U>{

    bool search(
        std::vector<bool> &visited, /*vector recording visitation*/ 
        uint32_t start,/*search from node*/
        uint32_t v /*node index being searched for*/)
    {
        std::stack<uint32_t> to_visit;
        to_visit.push(start);
        while (!to_visit.empty()){
            uint32_t current = to_visit.top();
            to_visit.pop();
            visited[current]=true; //record we've visited u        
            if (current==v) return true; //found the node
            for (auto it=this->edges[current].begin();it!=this->edges[current].end();++it)// loop over adjacency list of u
                if (!visited[it->first])
                    to_visit.push(it->first);
        }
        return false; 
    }

public:

    GraphDFSI(const uint32_t N):Graph<T,U>(N){}

    bool search(uint32_t v /*search node index*/)
    {
        uint32_t N = this->numVertices();
        std::vector<bool> visited(N,false); // set up visitation record
        for (size_t i = 0; i < N; ++i)
            if ((!visited[i])&&(search(visited,i,v))) //perform the search from i (if not visited) - return if found
                return true;
        return false;
    }
};

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
    
    GraphDFSI<T,U> graph(N);
    
    for (const auto & x: data)
        graph.addEdge(x.first,x.second);
 
    int32_t keyA = N*rnd(); //should be found
    int32_t keyB = N+10; //should not be found

    graph.print();
    std::cout<<std::endl;

    bool foundA = graph.search(keyA);
    bool foundB = graph.search(keyB);

    std::cout<<"key "<<keyA<<" ";
    if (foundA)
        std::cout<<"found"<<std::endl;
    else
        std::cout<<"not found"<<std::endl;
    std::cout<<"key "<<keyB<<" ";
    if (foundB)
        std::cout<<"found"<<std::endl;
    else
        std::cout<<"not found"<<std::endl;
        
    return 0;
}