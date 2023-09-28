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

Doubly Linked list

Properties: 
smart pointer to next node
raw pointer to prev node

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
the fourt line deletes c, the original p1, without any ownership of p2.
the last line sets the generalised destructor for the object to match the move
the default deleter object is just the "delete" command

*/

#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <memory>
#include <vector>

namespace structures_and_algorithms::structures::lists{

//Node class - in a normal implementation this would be private in the BinaryTree class to hide implementation
template<typename T>
struct DNode {
    T data;
    DNode<T> *prev = nullptr;
    std::unique_ptr<Node<T> > next = nullptr;
    DNode(T val,DNode<T> *ptr):data(val),prev(ptr){}  
    //~Node(){std::cout<<"deleting "<<data<<std::endl;} //for debugging
    ~DNode()
    {//should implement a destructor here in a loop to avoid recursion that occurs due to unique_ptrs   
        std::vector<std::unique_ptr<DNode<T> >* > to_delete;
        DNode<T>* ptr = this;
        while (ptr->next){
            to_delete.push_back(&(ptr->next));
            ptr = ptr->next.get();
        }
        for (auto it = to_delete.rbegin(); it != to_delete.rend(); ++it){          
            (*it)->reset();
        }
    }
};

//Doubly linked list class
template<typename T>
class DList{
protected:

    std::unique_ptr <DNode<T> > root = nullptr; //normally this would be private

    void printBelow(const std::unique_ptr<DNode<T> > &ptr) const
    {
        if (ptr){
            std::cout<<ptr->data<<std::endl;
            printBelow(ptr->next);
        }
    }
   
public:

    const std::unique_ptr<DNode<T> >& getRoot() const
    {
        return root;
    }

    std::unique_ptr<DNode<T> >& getRootVol() 
    {
        return root;
    }

    const std::unique_ptr<DNode<T> >* getRootPtr() const
    {
        return &root;
    }

    std::unique_ptr<DNode<T> >* getRootPtrVol()
    {
        return &root;
    }

    void print()
    {
        printBelow(root);
    }

    void push_back(T val)
    {
        std::unique_ptr <DNode<T> > *ptr = &root;
        DNode<T> *prev = nullptr;
        while (*ptr){
            prev = ptr->get();
            ptr = &((*ptr)->next);
        }
        *ptr = std::make_unique<DNode<T> >(val,prev);
    }

    void push_front(T val)
    {
        std::unique_ptr <DNode<T> > ptr = std::make_unique<DNode<T> >(val,nullptr);
        ptr->next = std::move(root);
        root = std::move(ptr);
    }

    bool insert(uint32_t index, T val)
    {
        std::unique_ptr <DNode<T> > *ptr = &root;  
        DNode *prev = nullptr; 
        for (uint32_t count = 0; count < index ; ++count) {//iterate through lsit
            //return false if we get to the end
            if (!(*ptr)) return false; //we allow ptr->next to be null (ptr!=null) to allow insertion at the end
            prev = (*ptr).get();
            ptr = &((*ptr)->next);
        }
        std::unique_ptr<DNode<T> > next = std::move(*ptr,prev); //hold the remainder of the list from this point
        (*ptr) = std::make_unique<DNode<T> > (val); //make and insert a node in the current ptr location    
        (*ptr)->next = std::move(next); //move the remainder into place
        (*ptr)->next.prev = (*ptr)->get(); //have the next node's prev pointer point towards the newly inserted node
        return true;
    }

    bool remove(uint32_t index)
    {
        std::unique_ptr <DNode<T> > *ptr = &root;
        DNode *prev = nullptr; 
        for (uint32_t count = 0; count < index ; ++count) {
            if (!ptr) return false;
            prev = (*ptr)->get();
            ptr = &((*ptr)->next);
        }
        (*ptr) = std::move((*ptr)->next);
        (*ptr).prev = prev;
        return true;
    }

    List(){}

    List(const std::vector<T> &data)
    {
        for (const auto &x:data)
            this->push_back(x);
    }

};

}

#endif /*DLIST_H*/
