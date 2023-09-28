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

Finds all connected clusters on a graph with iterative DFS

Input: Graph
Output: vector of cluster membersip (intger) for all nodes

Time: O(log(V))
Space: O(log(V))

*/

#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include "graph.hpp"
#include "random.hpp"

using namespace structures_and_algorithms::structures::graphs;
using namespace structures_and_algorithms::random;

struct clusterInfo{
    std::vector<uint32_t> clusterList;
    uint32_t numClusters;
};

template<typename T,typename U>
class GraphCluster : public Graph<T,U>{
    void search(
        std::vector<uint32_t> &visited, /*vector recording visitation/cluster*/ 
        uint32_t u,/*search from node*/
        uint32_t cluster /*cluster index being recorded*/)
    {
        std::stack<int32_t> to_visit;
        to_visit.push(u);
        while (!to_visit.empty()){
            uint32_t current = to_visit.top();
            to_visit.pop();
            visited[current]=cluster; //record we've visited u        
            for (auto it=this->edges[current].begin();it!=this->edges[current].end();++it)// loop over adjacency list of u
                if (!visited[it->first])
                    to_visit.push(it->first);
        }
    }
public:
    GraphCluster(const uint32_t N):Graph<T,U>(N){}

    //entry point function - start from all possible nodes
    clusterInfo getClusters()
    {
        uint32_t N = this->numVertices();
        std::vector<uint32_t> visited(N,0); // set up visitation/cluster record
        uint32_t cluster = 0;
        
        for (size_t i = 0; i < N; ++i){
            if (!visited[i]){
                ++cluster;
                search(visited,i,cluster); //perform the search from i (if not visited) - return if found
            }
        }
        return {visited,cluster};
    }
};

int main(/*int argc, char* argv[]*/)
{
    int32_t numNodes = 10;
    int32_t numEdges = 10;
    RndUniform rnd;
    std::vector<std::pair<int32_t,int32_t> > data(numEdges);
    
    for (auto & x: data){
        x.first=numNodes*rnd();
        x.second = x.first;
        while (x.second == x.first)
            x.second=numNodes*rnd();
    }
    
    typedef int32_t T;
    typedef int32_t U;
    GraphCluster<T,U> graph(numNodes);
    
    for (const auto & x: data){
        graph.addEdge(x.first,x.second);
        graph.addEdge(x.second,x.first);//make it undirected
    }
    
    std::cout<<"graph edges"<<std::endl;
    graph.print();

    clusterInfo clusters = graph.getClusters();
    std::cout<<std::endl;
    std::cout<<clusters.numClusters<<" clusters found"<<std::endl;
    std::cout<<"cluster membership"<<std::endl;
    for (uint c = 1; c <= clusters.numClusters; ++c){
        std::cout<<c<<" : ";
        for (size_t i=0;i<clusters.clusterList.size();++i)
            if (clusters.clusterList[i]==c)
                std::cout<<i<<" ";
        std::cout<<std::endl;
    }

    return 0;
}