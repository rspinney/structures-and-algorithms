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

QUEUE - list based FIFO/LILO data structure - variable lenth

*/

#ifndef QUEUE_H
#define QUEUE_H

#include <memory>

namespace structures_and_algorithms::structures::queues{

//Queue
template<typename T>
class Queue{
protected:
    struct Node{
        T data;
        std::unique_ptr<Node> next;
        template<typename V>
        Node(V &&val):data(std::forward<T>(val)){}
    };
    std::unique_ptr<Node> root;
    std::unique_ptr<Node> *back;
public:
    void pop()
    {
        root = std::move(root->next);
    }
    template<typename V>
    void push(V&& val)
    {
        *back = std::make_unique<Node>(Node(std::forward<V>(val)));
        back = &(*back)->next;
    }
    T front()
    {
       return root->data;
    }
    Queue():back(&root){}
};

}

#endif /*QUEUE_H*/
