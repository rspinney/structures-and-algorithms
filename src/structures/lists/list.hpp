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

Simple Linked list

Properties: pointer to next in line

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

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <memory>
#include <vector>

namespace structures_and_algorithms::structures::lists{

//List class
template<typename T>
class List{
protected:
    //encapsulate nodes in the list
    struct Node {
        T data;
        std::unique_ptr<Node> next = nullptr;
        template<typename V>
        Node(V &&val):data(std::forward<V>(val)){}  
        ~Node()// we implement a destructor with a loop to avoid recursion + poss stack overflow
        {      // that occurs due to unique_ptrs freeing everything they own top to bottom  
            std::vector<std::unique_ptr<Node>* > to_delete;
            Node* ptr = this;
            while (ptr->next){
                to_delete.push_back(&(ptr->next));
                ptr = ptr->next.get();
            }
            //all the destructing is called one node at a time from end of list to top due to reverse iteration
            for (auto it = to_delete.rbegin(); it != to_delete.rend(); ++it){    //reverse iteration is crucial
                (*it)->reset();
            }
        }
    };

    size_t N;
    std::unique_ptr <Node> root = nullptr;

    void printBelow(const std::unique_ptr<Node> &ptr) const
    {
        if (ptr){
            std::cout<<ptr->data<<std::endl;
            printBelow(ptr->next);
        }
    }
   
public:

    size_t size()
    {
        return N;
    }

    size_t sizeExplicit()
    {
        size_t n = 0;
        std::unique_ptr<Node> *ptr = &root;
        while(*ptr){
            ptr = &((*ptr)->next);
            ++n;
        }
        return n;
    }

    const std::unique_ptr<Node>& getRoot() const
    {
        return root;
    }

    std::unique_ptr<Node>& getRootVol() 
    {
        return root;
    }

    const std::unique_ptr<Node>* getRootPtr() const
    {
        return &root;
    }

    std::unique_ptr<Node>* getRootPtrVol()
    {
        return &root;
    }

    void print()
    {
        printBelow(root);
    }

    template<typename V>
    void push_back(V &&val)
    {
        std::unique_ptr <Node> *ptr = &root;
        while (*ptr){
            ptr = &((*ptr)->next);
        }
        *ptr = std::make_unique<Node>(std::forward<V>(val));
        ++N;
    }

    template<typename V>
    void push_front(V &&val)
    {
        std::unique_ptr <Node> ptr = std::make_unique<Node>(std::forward<V>(val));
        ptr->next = std::move(root);
        root = std::move(ptr);
        ++N;
    }

    template<typename V>
    bool insert(uint32_t index, V &&val)
    {
        std::unique_ptr <Node> *ptr = &root;   
        for (uint32_t count = 0; count < index ; ++count) {//iterate through lsit
            //return false if we get to the end
            if (!(*ptr)) return false; //we allow ptr->next to be null (ptr!=null) to allow insertion at the end
            ptr = &((*ptr)->next);
        }
        std::unique_ptr<Node> next = std::move(*ptr); //hold the remainder of the list from this point
        (*ptr) = std::make_unique<Node> (std::forward<V>(val)); //make and insert a node in the current ptr location
        (*ptr)->next = std::move(next); //move the remainder into place
        ++N;
        return true;
    }

    bool remove(uint32_t index)
    {
        std::unique_ptr <Node> *ptr = &root;    
        for (uint32_t count = 0; count < index ; ++count) {
            if (!ptr) return false;
            ptr = &((*ptr)->next);
        }
        (*ptr) = std::move((*ptr)->next);
        --N;
        return true;
    }

    List():N(0){}

    // attempt at perfect forwarding a vector in order to 1-by-1 use its elements
    template<typename VectorT>
    List(VectorT &&data):N(data.size())
    {
        std::vector<T> temp = std::forward<VectorT>(data);
        for (auto &&x:temp)
            this->push_back(std::move(x));
    }

};

}

#endif /*LIST_H*/
