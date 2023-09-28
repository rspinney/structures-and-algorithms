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

reverse an array

*/

#include <iostream>
#include <vector>  
#include <algorithm> 

template<typename T>
void reverse(std::vector<T> &data) {
    size_t n = data.size();
    for(size_t i=0;i<n/2;++i)
        std::swap(data[i],data[n-1-i]);
}


int main(){
    std::vector<int> data{1,2,3,4,5,6,7,8,9,10,11};
    reverse(data);
    for (const auto &x:data)
        std::cout<<x<<" ";
    std::cout<<std::endl;
}