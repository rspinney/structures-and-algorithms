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

Simple queue - circular fixed siz

*/

#include <iostream>
#include <vector>
#include "queue_circ.hpp"

using namespace structures_and_algorithms::structures::queues;

int main(/*int argc, char* argv[]*/)
{   
    typedef int32_t T;
    QueueStatic<T,10> queue{};
    queue.push(10);
    queue.push(20);
    queue.push(30);
    queue.push(40);
    
    std::cout<<queue.front()<<std::endl;
    queue.pop();
    std::cout<<queue.front()<<std::endl;
    queue.pop();
    std::cout<<queue.front()<<std::endl;
    queue.pop();
    queue.push(10);
    queue.push(20);
    queue.push(30);
    std::cout<<queue.front()<<std::endl;
    queue.pop();
    std::cout<<queue.front()<<std::endl;
    queue.pop();
    std::cout<<queue.front()<<std::endl;
    queue.pop();
    
    return 0;  
}