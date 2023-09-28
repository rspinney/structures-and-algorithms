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

Binary search tree - with deletion and insertion

*/

#include <iostream>
#include <memory>
#include <vector>
#include "binary_tree.hpp"
#include "random.hpp"

using namespace structures_and_algorithms::structures::trees;
using namespace structures_and_algorithms::random;

int main(/*int argc, char* argv[]*/)
{
    RndUniform rnd;

    std::cout<<"making tree"<<std::endl;
    std::vector<int32_t> data(20,0);
    for (auto i=0;i<20;++i)
        data[i]=100*rnd();
    BinaryTree<int32_t> tree(data);
    std::cout<<"printing tree"<<std::endl;
    tree.print();
    std::cout<<"deleting value "<<data[10]<<std::endl;
    if (tree.remove(data[10])){
        std::cout<<"sucess"<<std::endl;
        std::cout<<"printing tree"<<std::endl;
        tree.print();
    }
    else
        std::cout<<"key not in tree"<<std::endl;
    std::cout<<"deleting value "<<101<<std::endl;
    if (tree.remove(101)){
        std::cout<<"sucess"<<std::endl;
        std::cout<<"printing tree"<<std::endl;
        tree.print();
    }
    else
        std::cout<<"key not in tree"<<std::endl;        
    
    
    std::cout<<"Printing in order"<<std::endl;
    tree.printInOrder();
    std::cout<<"Printing in order"<<std::endl;
    tree.printInOrder2(tree.getRoot());

    std::cout<<"exiting"<<std::endl;
    return 0;
}