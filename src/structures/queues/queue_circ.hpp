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

QUEUE - circular FIFO/LILO data structure - fixed size N

*/

#ifndef QUEUESTATIC_H
#define QUEUESTATIC_H

#include <iostream>
#include <memory>
#include <array>

namespace structures_and_algorithms::structures::queues{

//Queue
template<typename T,size_t N>
class QueueStatic{
protected:
    std::array<T,N> data;
    size_t front_=0;
    size_t back_=0;
public:
    void pop()
    {
        front_ = (front_+1)%N;
    }
    template<typename V>
    void push(V &&val)
    {
        data[back_]=std::forward<V>(val);
        back_ = (back_+1)%N;
    }
    T front()
    {
       return data[front_];
    }
    QueueStatic()
    {}
};

}

#endif /*QUEUESTATIC_H*/
