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

Depth First Search for a tree - NON Recursive

Input: Binary Tree, key
Output: boolean found/not found

Time: O(log(n))
Space: O(1)

As ever we use a stack to keep track of nodes we need to visit

Explicitly, 
    1) initialise the stack with initial node
    2) Loop;
        a) search/check node at top of the stack
        b) pop the stack
        c) push children onto the stack (if they are not nullptr)
    3) Exit when stack is empty - all nodes searched

//SAME as depth first except using a stack instead of a queue

*/

#include <iostream>
#include <stack>
#include "binary_tree.hpp"
#include "random.hpp"

using namespace structures_and_algorithms::structures::trees;
using namespace structures_and_algorithms::random;

template<typename T>
class BinaryTreeDFSI : public BinaryTree<T>{
    typedef typename BinaryTree<T>::Node Node; // nested class Node in BinaryTree is now dependent type
public:
    BinaryTreeDFSI():BinaryTree<T>(){}
    BinaryTreeDFSI(const std::vector<T> &data):BinaryTree<T>(data){}
 
    bool search(const T key) const
    {
        std::stack<const std::unique_ptr<Node> *> to_visit;
        to_visit.push(&(this->root));
        while (!to_visit.empty()){
            const std::unique_ptr<Node>* current = to_visit.top();
            if ((*current)->data == key){
                return true;
            }
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
    BinaryTreeDFSI<int32_t> tree(data);

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