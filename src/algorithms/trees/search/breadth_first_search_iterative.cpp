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

Breadth First Search for a tree - NON Recursive

Input: Binary Tree, key
Output: boolean found/not found

Time: O(log(n))
Space: O(1)

Here we use a queue (not a stack) to keep track of nodes we need to visit 
- exactly the same as DFS except new nodes are added to the end of the data structure

Explicitly, 
    1) initialise the queue with initial node
    2) Loop;
        a) search/check node at frontof the queue
        b) pop the front of the queue
        c) push children onto the BACK of the queuee (if they are not nullptr)
    3) Exit when queue is empty - all nodes searched

Note how all children of a node are searched in order due to how they enter the queue

//SAME as depth first except using a queue instead of a stack

*/

#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include "binary_tree.hpp"
#include "random.hpp"

using namespace structures_and_algorithms::structures::trees;
using namespace structures_and_algorithms::random;

template<typename T>
class BinaryTreeBFSI : public BinaryTree<T>{
    typedef typename BinaryTree<T>::Node Node; // nested class Node in BinaryTree is now dependent type
public:
    BinaryTreeBFSI():BinaryTree<T>(){}
    BinaryTreeBFSI(const std::vector<T> &data):BinaryTree<T>(data){}

    bool search(const T key){
        std::queue<const std::unique_ptr<Node> *> to_visit;
        to_visit.push(&(this->root));
        while (!to_visit.empty()){
            const std::unique_ptr<Node>* current = to_visit.front();
            if ((*current)->data == key)
                return true;
            to_visit.pop();
            if ((*current)->left)
                to_visit.push(&(*current)->left);
            if ((*current)->right)
                to_visit.push(&(*current)->right);            
        }
        return false;
    }
};

int main(/*int argc, char* argv[]*/)
{
    RndUniform rnd;
    std::vector<int32_t> data(20,0);
    for (auto i=0;i<20;++i)
        data[i]=100*rnd();
    BinaryTreeBFSI<int32_t> tree(data);

    int32_t keyA = data[10]; //should be found
    int32_t keyB = 104; //should not be found

    tree.print();
    std::cout<<std::endl;

    bool foundA = tree.search(keyA);
    bool foundB = tree.search(keyB);

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