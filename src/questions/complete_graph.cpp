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

Number of reconnections to graph needed to make it connected (i.e. fully traversable)

Explicitly, how many times do we need to " remove a connection + add another connection "
to make the graph complete.

We make use of the property that:

    A graph with N vertices can be made complete with N-1 edges - e.g. by just building a ring.

So - immediately we know the task is possible if there are N-1 or more edges

To inform how many connections need to be rewired we need to know how many connected components
there are - which we can do with a normal DFS cluster search.

If there are M clusters, we thus need to rewire M-1 edges to connect them.

So the answer is M-1, unless  |E| < N-1, in which case it is impossible.

*/

#include <iostream>
#include <list>
#include <vector>
#include <array>
#include <string>

//make adjacency lists out of adjacency matrix
template<size_t N>
std::vector<std::list<uint32_t> > makeAdjLists(const std::array<std::array<size_t,N>,N> &adjMatrix, size_t &numEdges)
{
    numEdges = 0;
    std::vector<std::list<uint32_t> > adjLists(N,std::list<uint32_t>{});
    for (size_t i =0;i<adjMatrix.size();++i){
        for (size_t j =0;j<adjMatrix[i].size();++j){
            if (adjMatrix[i][j]){
                adjLists[i].push_back(j);
                ++numEdges;
            }
        }
    }
    return adjLists;
}

//make adjacency lists out of adjacency list
std::vector<std::list<uint32_t> > makeAdjLists(size_t N,const std::vector<std::array<size_t,2>> &adjList, size_t &numEdges)
{
    numEdges = 0;
    std::vector<std::list<uint32_t> > adjLists(N,std::list<uint32_t>{});
    for (size_t i =0;i<adjList.size();++i){
        adjLists[adjList[i][0]].push_back(adjList[i][1]);
        ++numEdges;    
    }
    return adjLists;
}

//DFS setting visited element to true
void DFS(const std::vector<std::list<uint32_t> > &adjLists, std::vector<bool> &visited,const size_t i)
{
    for (const auto &x:adjLists[i]){//loop over neighbours
        if (!visited[x]){
            visited[x] = true;
            DFS(adjLists,visited,x);
        }
    }
}

size_t numComponents(const std::vector<std::list<uint32_t> > &adjLists)
{
    std::vector<bool> visited(adjLists.size(),false);
    size_t numClusters = 0;
    for (size_t i=0;i<adjLists.size();++i){
        if (!visited[i]){
            DFS(adjLists,visited,i);
            ++numClusters;//we have a new cluster if we could only get to it in this loop
        }
        visited[i] = true;
    }
    return numClusters;
}

int main(/*int argc, char* argv[]*/)
{
    size_t N = 4;
    std::vector<std::array<size_t,2>> adjList =
    {
        { 0, 1 }, 
        { 0, 2 }, 
        { 1, 2 }
    };
    size_t edges = 0;
    auto adjLists = makeAdjLists(N,adjList,edges);
    size_t C = numComponents(adjLists);
    size_t freeEdges = N-1;
    if (freeEdges >= C-1)
        std::cout<<C-1<<" change(s) required"<<std::endl;
    else
        std::cout<<"not possible"<<std::endl;
    return 0;
}
