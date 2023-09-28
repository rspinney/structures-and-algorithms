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

Simple stack

*/

#include <iostream>
#include "stack.hpp"

using namespace structures_and_algorithms::structures::stack;

int main(/*int argc, char* argv[]*/)
{   
    typedef int32_t T;
    Stack<T> stack{};
    stack.push(10);
    stack.push(20);
    stack.push(30);
    std::cout<<stack.top()<<std::endl;
    stack.pop();
    std::cout<<stack.top()<<std::endl;
    stack.pop();
    std::cout<<stack.top()<<std::endl;
    stack.pop();
    return 0;  
}