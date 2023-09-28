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

FizzBuzz

*/

#include <iostream>
#include <list>
#include <string>

int main(/*int argc, char* argv[]*/)
{
    std::list<std::pair<uint32_t,std::string> > tests;
    tests.push_back({3,"Fizz"});
    tests.push_back({5,"Buzz"});
    tests.push_back({7,"Bodge"});

    for (uint32_t i=0; i<200; ++i){
        std::string str;
        for (const auto &x : tests)
            if (!(i%x.first))
                str += x.second;
        if (!str.length())
            str = std::to_string(i);
        std::cout<<str<<std::endl;
    }
    return 0;
}
