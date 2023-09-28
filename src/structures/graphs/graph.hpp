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

Graph structure
Contains:
1) vector of vertex data of type T comprising all vertices
2) vector of lists of edge data with list at index i containing all outward edges from vertex i
    edge data comprised of a pair of outgoing vertex index, j,  and weight of edge i -> j

*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <type_traits>

namespace structures_and_algorithms::structures::graphs{

//graph class
template<typename T = size_t,typename U = uint8_t> //T value at nodes, U edge weights - default U to small unsigned int to hold edge weight 1
class Graph{
protected:
    std::vector<T> vertexData;
    std::vector<std::list<std::pair<uint32_t,U> > > edges;
public:

    uint32_t numVertices() const noexcept
    {
        return vertexData.size();
    }
    
    bool setValue(const uint32_t u, const T val)
    {
        uint32_t N = numVertices();
        if (u>=N)
            return false;
        vertexData[u]=val;
        return true;
    }

    template<typename V>
    bool addEdge(const uint32_t u, const uint32_t v, V &&val)
    {
        uint32_t N = numVertices();
        if ((u>=N)||(v>=N)||(u==v))
            return false;
        std::pair<uint32_t,U> entry = {v,std::forward<V>(val)};
        edges[u].push_back(std::move(entry));
        return true;
    }

    bool addEdge(const uint32_t u, const uint32_t v)
    {
        uint32_t N = numVertices();
        if ((u>=N)||(v>=N)||(u==v))
            return false;
        std::pair<uint32_t,U> entry = {v,U()};
        //if numeric type default edge weight is 1.
        if (std::is_arithmetic_v<U>) entry.second = static_cast<U>(1); 
        edges[u].push_back(std::move(entry));
        return true;
    }

    bool addEdgeUndirected(const uint32_t u, const uint32_t v, const U val)
    {
        return addEdge(u,v,val) && addEdge(v,u,val);
    }

    bool addEdgeUndirected(const uint32_t u, const uint32_t v)
    {
        return addEdge(u,v) && addEdge(v,u);
    }

    void insert()
    {
        vertexData.push_back(T());
        edges.push_back(std::list<std::pair<uint32_t,U> >());
    }
    template<typename V>
    void insert(V &&val)
    {
        vertexData.push_back(std::forward<V>(val));
        edges.push_back(std::list<std::pair<uint32_t,U> >());
    }
    Graph(){}
    Graph(const uint32_t N)
    {
        vertexData = std::vector<T>(N);
        edges = std::vector<std::list<std::pair<uint32_t,U> > > (N,std::list<std::pair<uint32_t,U> >());
    }

    void print()
    {
        for (size_t i=0;i<edges.size();++i){
            for (auto e=edges[i].begin();e!=edges[i].end();++e){
                std::cout<<i<<" "<<e->first<<std::endl;
            }
        }
    }
};

}

#endif /*GRAPH_H*/
