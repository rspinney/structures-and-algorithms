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

Simple Binary Search tree

Properties:
2 child nodes per parent node
left node is < parent node
right node is > parent node
assuming no duplicates

Methods implemented:
insert
delete/remove


Notes:
smart pointers p1,p2

p1=std::move(p2)

is equivalent to

p1->reset(p2.release());

which amount to something like

p2raw = p2.release();
c = p1.get();
p1.get() = p2raw;
if (c) get_deleter()(c)
get_deleter() = std::forward<Deleter>(r.get_deleter())

the first line frees the memory management of p2 and causes it not to be a candidate for deletion
the second line stores the address of p1
the third line moves the data accross
the fourth line deletes c, the original p1, without any ownership of p2.
the last line sets the generalised destructor for the object to match the move
the default deleter object is just the "delete" command

*/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <memory>
#include <vector>
#include <stack>

namespace structures_and_algorithms::structures::trees{

//Binary tree class
template<typename T>
class BinaryTree{
protected:

    struct Node {
        T data;
        std::unique_ptr<Node> left = nullptr;
        std::unique_ptr<Node> right = nullptr;
        Node(T val):data(val){}     
        ~Node(){//destructor deletes tree from bottom to top to avoid recursion
            std::vector<std::unique_ptr<Node>* > to_delete;
            std::stack<std::unique_ptr<Node>* > to_visit;
            to_visit.push(&(this->left));
            to_visit.push(&(this->right));
            while (!to_visit.empty()){ //add all child nodes in depth first manner
                std::unique_ptr<Node>* current = to_visit.top();
                to_visit.pop();
                if (*current){
                    to_delete.push_back(current);
                    if (&(*current)->left) to_visit.push(&((*current)->left));
                    if (&(*current)->right) to_visit.push(&((*current)->right));        
                }
            }
            for (auto it = to_delete.rbegin(); it != to_delete.rend(); ++it){ //delete in reverse order         
                (*it)->reset();
            }
        }
    };

    std::unique_ptr <Node> root = nullptr; 

    void insert(std::unique_ptr<Node> &ptr,T val){
        if (ptr){
            if (val >= ptr->data)
                this->insert(ptr->right,val);
            else
                this->insert(ptr->left,val);
        }
        else{
            ptr = std::make_unique<Node>(val);
        }
    }

    void printBelow(const std::unique_ptr<Node> &ptr) const{
        if (ptr){
            std::cout<<ptr->data<<std::endl;
            printBelow(ptr->left);
            printBelow(ptr->right);
        }
    }

    std::unique_ptr<Node>& findMin(std::unique_ptr<Node> &ptr)
    {
        std::unique_ptr<Node> *current = &ptr;
        while (true) {
            if (*current && (*current)->left == nullptr)
                return (*current); //return the reference to the node with no further left child - i.e. the minimum in the tree as measured from ptr
            current = &(*current)->left;
        }
    }

    bool remove(std::unique_ptr<Node> &ptr,T val){
        if (!ptr){ //reached end of tree - value not found
            return false;
        }
        else if (ptr->data == val){ // remove this node
            if (ptr->left){ //there is at least a left (<) child
                
                if (ptr->right){ // we have both a left and right child                    
                    //get reference to smallest node which has data that is larger than ptr->data
                    std::unique_ptr<Node>& nextMin = findMin(ptr->right);
                    //set the node to deleted's data with the smallest on r.h.s. (ie. so that it fits in the tree)
                    ptr->data = nextMin->data;
                    //delete the (now duplicate) data that we copied from lower down
                    return remove(nextMin,nextMin->data);
                }
                else{ // we only have left child
                    ptr = std::move(ptr->left);
                    //exchange node to be removed with the single left child
                }
            }
            else{ // there is at most a single right (>) child
                ptr = std::move(ptr->right); 
                //exchange node to be removed with right child - right child can be null
            }
            return true;
        }
        else{ // node to be deleted is further down the tree
            if (val < ptr->data)
                return remove(ptr->left,val);
            else
                return remove(ptr->right,val);
        }
    }

public:

    const std::unique_ptr<Node>& getRoot() const{
        return root;
    }

    const std::unique_ptr<Node>* getRootPtr() const{
        return &root;
    }

    void printInOrder(){
        //depth first
        std::stack<Node*> to_visit;
        Node *current = root.get();
        while ((!to_visit.empty())||(current)){

            while (current){
                to_visit.push(current);
                current = current->left.get();
            }

            current = to_visit.top();
            to_visit.pop();
            std::cout<<current->data<<std::endl;
            current = current->right.get();
        }
    }

    void printInOrder2(const std::unique_ptr<Node> &ptr){
        if (!ptr)
            return;
        if (ptr->left)
            printInOrder2(ptr->left);
        std::cout<<ptr->data<<std::endl;
        if (ptr->right)
            printInOrder2(ptr->right);
    
    }

    void print(){
        printBelow(root);
    }

    bool remove(T val){
        return remove(root,val);
    }

    void insert(T val){
        this->insert(root,val);
    }

    BinaryTree(const std::vector<T> &data){
        for (const auto &x:data)
            this->insert(x);
    }

};

}

#endif /*BINARY_TREE_H*/
