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

Depth First Search for a tree - Recursive

Input: Binary Tree, key
Output: boolean found/not found

Time: O(log(n))
Space: O(log(n))

Notes: general concerns about recursion - space complexity due to number of stack frames

*/

#include <iostream>
#include <memory>
#include <vector>
#include "binary_tree.hpp"
#include "random.hpp"

using namespace structures_and_algorithms::structures::trees;
using namespace structures_and_algorithms::random;

template<typename T>
class BinaryTreeDFSR : public BinaryTree<T>{
    typedef typename BinaryTree<T>::Node Node; // nested class Node in BinaryTree is now dependent type
    bool searchR(const std::unique_ptr<Node> &ptr,const T val){
        if (!ptr) return false;
        if (ptr->data == val) return true;
        return (searchR(ptr->left,val) || searchR(ptr->right,val));
    }
public:
    BinaryTreeDFSR():BinaryTree<T>(){}
    BinaryTreeDFSR(const std::vector<T> &data):BinaryTree<T>(data){}

    bool search(const T val){
        if (!this->root) return false;
        if (this->root->data == val) return true;
        return (searchR(this->root->left,val) || searchR(this->root->right,val));
    }
};

int main(/*int argc, char* argv[]*/)
{
    RndUniform rnd;
    std::vector<int32_t> data(20,0);
    for (auto i=0;i<20;++i)
        data[i]=100*rnd();
    BinaryTreeDFSR<int32_t> tree(data);
    
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