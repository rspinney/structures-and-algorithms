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

Linked list- with push_front and push_back

*/

#include <iostream>
#include "list.hpp"

using namespace structures_and_algorithms::structures::lists;

int main(/*int argc, char* argv[]*/)
{
    std::cout<<"making list"<<std::endl;
    List<int32_t> list{};
    for (int32_t i=0;i<10;i++)
        list.push_front(i);
    for (int32_t i=10;i<20;i++)
        list.push_back(i);
    std::cout<<"printing list"<<std::endl;
    list.print();
    std::cout<<"inserting 100 at index 2"<<std::endl;
    list.insert(2,100);
    list.print();
    std::cout<<"removing index 2"<<std::endl;
    list.remove(2);
    list.print();
    std::cout<<"removing index 0"<<std::endl;
    list.remove(0);
    list.print();      
    return 0;
}