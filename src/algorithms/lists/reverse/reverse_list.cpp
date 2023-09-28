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

Reverses a linked list

// works as follows:

1. pointers to  "current", "next" and "prev" in list at position i
    "prev" initilaised to null
        prev = nullptr
    "current" initialised to root
        current = root
    "next" not initlaised.
2. "next" set equal to current->next i.e. i+1
    next = current->next
3. "current" changed to point at "prev" i.e. for i to point at  i-1 - this is the reversing part
    current->next = prev
4. "prev" set equal to current, at position i, (i.e "prev" is bumped along one)
    prev = current
5. "current" set equal to "next", at position i+1, (i.e. "current" is bumped along one)
    current = next
6. at the end the last valid point occupies the "prev" placeholder, so set root = prev
    root = prev
7. we are using smart pointers so all "assignments" are replaced with move operations


*/

#include <iostream>
#include "list.hpp"

using namespace structures_and_algorithms::structures::lists;

template<typename T>
class ListReverse : public List<T>{
    typedef typename List<T>::Node Node; // nested class Node in List is now dependent type
public:
    ListReverse():List<T>(){}
    ListReverse(const std::vector<T> &data):List<T>(data){}

    void reverse()
    {
        std::unique_ptr<Node> &current = this->root;
        std::unique_ptr<Node> prev = nullptr;
        std::unique_ptr<Node> next = nullptr;
        while (current){
            next = std::move(current->next);
            current->next = std::move(prev);
            prev = std::move(current);
            current = std::move(next);
        }
        this->root = std::move(prev);
    }
};

int main(/*int argc, char* argv[]*/)
{
    ListReverse<int32_t> list{}; //avoid most vexing parse!
    for (int32_t i=9;i>0;i--)
        list.push_front(i);
    std::cout<<"initial list"<<std::endl<<std::endl;
    list.print();
    list.reverse();
    std::cout<<std::endl<<"reversed list"<<std::endl<<std::endl;
    list.print();
}