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

Stack - simple LIFO data structure

*/

#ifndef STACK_H
#define STACK_H

#include <vector>

namespace structures_and_algorithms::structures::stack{

//HashTable class
template<typename T>
class Stack{
protected:
    std::vector<T> data;
public:
    void pop()
    {
        data.pop_back();
    } 
    template<typename V> 
    void push(V &&val)
    {
        data.emplace_back(std::forward<V>(val));
    }
    T top()
    {
       return data.back();
    }
    Stack(const std::vector<T> &data_):data(data_)
    {}
    Stack()
    {}
};

}

#endif /*STACK_H*/
