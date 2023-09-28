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

#include <iostream>
#include <stack>
#include "binary_tree.hpp"
#include "random.hpp"

using namespace structures_and_algorithms::structures::trees;
using namespace structures_and_algorithms::random;

template<typename T>
class BinaryTreeReverse : public BinaryTree<T>{
    typedef typename BinaryTree<T>::Node Node; // nested class Node in BinaryTree is now dependent type
    void reverseRecursive(const std::unique_ptr<Node> &ptr){
        if (!ptr)
            return;
        if (ptr->left)
            reverseRecursive(ptr->left);
        if (ptr->right)
            reverseRecursive(ptr->right);
        std::swap(ptr->left,ptr->right);
    }
public:

    void reverseRecursive(){ //entry point
        reverseRecursive(this->root);
    }

    void reverseIterative(){
        //depth first
        std::stack< Node*> to_visit;
        Node*current = this->root.get();
        to_visit.push(current);
        while (!to_visit.empty()){
            current = to_visit.top();
            to_visit.pop();
            std::swap(current->left,current->right);
            if (current->left.get())
                to_visit.push(current->left.get());
            if (current->right.get())
                to_visit.push(current->right.get());
        }
    }
    
    BinaryTreeReverse():BinaryTree<T>(){}
    BinaryTreeReverse(const std::vector<T> &data):BinaryTree<T>(data){}
};

int main(/*int argc, char* argv[]*/)
{
    typedef int32_t T;
    RndUniform rnd;
    std::vector<T> data(20,0);
    for (auto i=0;i<20;++i)
        data[i]=100*rnd();
    BinaryTreeReverse<T> tree(data);

    std::cout<<"printing"<<std::endl;
    tree.printInOrder();
    tree.reverseRecursive();
    std::cout<<"printing"<<std::endl;
    tree.printInOrder();
       
    return 0;
}