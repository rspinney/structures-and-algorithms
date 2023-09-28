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

Dijkstra Shortest paths algorithm.

Greedy algorithm for finding shortest paths/and their lengths from a specified vertex, 
to all other vertices on a graph.

Complexity: 
    Using naive search   : O(|V|^2)            - implemented
    Using min-heap       : O((|V|+|E|)log |V|) - implemented
    Using Fibonnaci heap : O(|E|+|V|log |V|)   - not implemented

Restrictions:
    Edge weights must be positive

Fundamentally exploits the property that:

    The minimum distance to a vertex from the origin must be the distance from the origin 
    to one of its neighbours to the origin, plus the distance from the neighbour to the vertex.

Consequently, by starting at the origin and working our way out, we can visit vertices with
established minimum distances and thus determine possible minimum distances to all the current 
vertex's neighbours by comparing the current tentative values associated with the neighbours 
with the current vertex distance + the known inter-neighbour distances.

The minimum updated distance is then a candidate for the shortest route to any given vertex, as 
it is the smallest path out from the origin found so far.

So, we:

1. Visit all vertices eventually, starting at the origin - with distance to origin 0.
2. Know that the distance we have recorded to the current vertex is minimal
3. Update proposed minimal distances to all neighbours of the current vertex using edge weights
4. Remove the current vertex from the possible traversal candidates (we know its minimal distance)
5. Visit the vertex with the smallest minimal distance is an unvisited set - this is now known to 
   be the minimal distance
   It has to be minimal, because of the key property above and the fact we tested all other edges
   from its minimal neighbour - we can't find a shorter way to this vertex as it would at least
   incur an edge weight greater than the immediate step we just took.
6. iterate until all vertices visited

The key optimisation part of the algorithm is in the "visit vertex with smallest minimum distance". 
By using a priority queue, e.g. through a heap, we can improve this - by keeping small values at the front. 
We need to extend a regular minHeap because we need to access the neighbours of the minium element within 
the heap, updated them, and then re-heapify the heap - i.e. send new smallest values to the front.

Here we do this with class "IndexedHeap" which hashes elements in the heap to their index in the underlying 
array. We need to update key functions like "swap" so these hashed indices swap when data in the heap is 
moved around in sendUp(),sendDown() etc. calls.

*/

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <cmath>
#include "graph.hpp"
#include "heap.hpp"
#include "indexedheap.hpp"

using namespace structures_and_algorithms::structures::graphs;
using namespace structures_and_algorithms::structures::heaps;

#define MAXDIST std::pow(2,16) // should do for this example

//struct for route info from origin vertex
template<typename U>
struct Routes{
    size_t origin;
    std::vector<U> distances;
    std::vector<int32_t> previous;
};

//Extend Graph class
template<typename T,typename U> //T value at nodes, U edge weights
class DijkstraGraph : public Graph<T,U>
{  
    //encapsulation of vertex index and distance with comparison overloads for heap version
    struct IndexWeight
    {
        size_t vertex;
        U weight;    
        bool operator< (const IndexWeight& A) const { return this->weight < A.weight;};
        bool operator> (const IndexWeight& A) const { return this->weight > A.weight;};
        IndexWeight(){}
        template<typename V,typename W>
        IndexWeight(V &&v_, W &&w_):vertex(std::forward<V>(v_)),weight(std::forward<W>(w_)){}
        bool operator==(const IndexWeight &val)const noexcept{return this->vertex == val.vertex;}
        //need == operator for hashtable
    };

    //find minimum unvisited distance for simple version
    size_t findMinIndex(const std::vector<bool> &visited,const std::vector<U> &distances) const
    {
        U runningMin = MAXDIST;
        size_t index = 0;
        for (size_t i=0;i<this->vertexData.size();++i){
            if ((!visited[i])&&(distances[i]<runningMin)){
                runningMin = distances[i];
                index = i;
            }
        }
        return index;
    }

public:
    DijkstraGraph(): Graph<T,U>(){}
    DijkstraGraph(const uint32_t N): Graph<T,U>(N){}

    //distance and routes to all nodes by default - will stop if endVertex reached
    Routes<U> dijkstraSimple(size_t startVertex, size_t endVertex = -1) const
    {
        //test for OOB
        if (startVertex >= this->vertexData.size())
            return {};
        //record of visitation
        std::vector<bool> visited(this->vertexData.size(),false); 
        //distance values
        std::vector<U> distances(this->vertexData.size(),MAXDIST);
        distances[startVertex] = static_cast<U>(0);//zero distance to itself
        //previous vertex for path iteration
        std::vector<int32_t> previous(this->vertexData.size(),-1); 
        previous[startVertex] = startVertex;

        size_t count = 0;
        while(count < this->vertexData.size()){ //visit every vertex           
            size_t currentVertex = findMinIndex(visited,distances); //get vertex currently "closest" to start
            for (auto & neighbourData : this->edges[currentVertex]){ //loop of neighbours
                const uint32_t &neighbourVertex = neighbourData.first; //neighbour vertex
                const U &neighbourDistance = neighbourData.second; //distance from current to neighbour
                if (!visited[neighbourVertex]){ //if neighbour not previously visited
                    U newDist = distances[currentVertex] + neighbourDistance; //proposed new distance to neighbour from start
                    if (newDist < distances[neighbourVertex]){ //if lower
                            distances[neighbourVertex] = newDist; //update distance to neighbour from start
                            previous[neighbourVertex] = currentVertex; //update previous vertex to neighbour in path
                    }
                }
            }
            visited[currentVertex] = true; //mark current vertex as visited
            ++count;
            if (currentVertex == endVertex)
                break;
        }
        return {startVertex,std::move(distances),std::move(previous)};
    }

    //distance and routes to all nodes by default - will stop if endVertex reached
    Routes<U> dijkstraHeap(size_t startVertex, size_t endVertex = -1) const
    {
        //test for OOB
        if (startVertex >= this->vertexData.size())
            return {};
        //record of visitation
        std::vector<bool> visited(this->vertexData.size(),false); 
        visited[startVertex] = true;
        //distance values
        std::vector<U> distances(this->vertexData.size(),MAXDIST);
        distances[startVertex] = static_cast<U>(0); //zero distance to itself
        //previous vertex for path iteration
        std::vector<int32_t> previous(this->vertexData.size(),-1); 
        previous[startVertex] = startVertex;
        //minheap as priority queue
        Heap<IndexWeight> distancesHeap;
        distancesHeap.insert({startVertex,0});

        while(!distancesHeap.isEmpty()){            
            IndexWeight currentVertex = distancesHeap.getRoot(); //get currently "closest" node from heap - by value as insertions below
            for (auto & neighbourData : this->edges[currentVertex.vertex]){//loop through neighbours
                const uint32_t &neighbourVertex = neighbourData.first; //vertex of neighbour
                const U &neighbourDistance = neighbourData.second; //distance to neighbour from current
                if (!visited[neighbourVertex]){ //if unvisited
                    U newDist = currentVertex.weight + neighbourDistance; //trial distance
                    if (newDist < distances[neighbourVertex]){ //if closer
                            distances[neighbourVertex] = newDist; //update distance to neighbour
                            previous[neighbourVertex] = currentVertex.vertex; //update previous vertex in path
                            distancesHeap.insert({neighbourVertex,newDist}); // add new (non infinity) distance into priority queue
                    }
                }
            }
            visited[currentVertex.vertex] = true; //mark current vertex as visited
            if (currentVertex.vertex == endVertex)
                break;
            distancesHeap.removeRoot(); //remove visited vertex from heap
        }
        return {startVertex,std::move(distances),std::move(previous)};
    }
};

auto main(/*int argc, char* argv[]*/)->int
{
    typedef int32_t T;
    typedef int32_t U;
    int32_t N = 9;    // number of vertices in graph 
    DijkstraGraph<T,U> graph(N); //uses ./sample_graph.jpeg
    graph.addEdgeUndirected(0,1,4);
    graph.addEdgeUndirected(0,7,8);
    graph.addEdgeUndirected(1,7,11);
    graph.addEdgeUndirected(1,2,8);
    graph.addEdgeUndirected(7,6,1);
    graph.addEdgeUndirected(7,8,7);
    graph.addEdgeUndirected(8,2,2);
    graph.addEdgeUndirected(6,8,6);
    graph.addEdgeUndirected(6,5,2);
    graph.addEdgeUndirected(2,3,7);
    graph.addEdgeUndirected(2,5,4);
    graph.addEdgeUndirected(5,3,14);
    graph.addEdgeUndirected(3,4,9);
    graph.addEdgeUndirected(5,4,10);
    
    //start vertex
    int32_t v = 0;

    //simple version
    std::cout<<"simple version"<<std::endl;
    Routes<U> routes = graph.dijkstraSimple(v);
    std::vector<U> &dists = routes.distances;
    std::vector<int32_t> &paths = routes.previous;
    std::cout<<"distances and paths from vertex "<<routes.origin<<std::endl;
    for (size_t i=0;i<dists.size();++i){
        std::cout<<i<<": "<<dists[i]<<std::endl<<"path (reversed) : ";
        int32_t u = i;
        std::cout<<u<<" ";
        while ((u != v)&&(u>=0)){
            std::cout<<paths[u]<<" ";
            u = paths[u];
        }
        std::cout<<std::endl<<std::endl;
    }

    //regular heap priority queue version
    std::cout<<std::endl<<std::endl<<"regular heap priority queue version"<<std::endl;
    Routes<U> routesH = graph.dijkstraHeap(v);
    std::vector<U> &distsH = routesH.distances;
    std::vector<int32_t> &pathsH = routesH.previous;
    std::cout<<"distances and paths from vertex "<<routes.origin<<std::endl;
    for (size_t i=0;i<distsH.size();++i){
        std::cout<<i<<": "<<distsH[i]<<std::endl<<"path (reversed) : ";
        int32_t u = i;
        std::cout<<u<<" ";
        while ((u != v)&&(u>=0)){
            std::cout<<pathsH[u]<<" ";
            u = pathsH[u];
        }
        std::cout<<std::endl<<std::endl;
    }

    return 0;
}