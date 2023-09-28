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

rotate a given circular array by k places

*/

#include <iostream>
#include <vector>  
#include <algorithm> 

class Solution {
public:
    void circularShift(std::vector<int> &data, int k) {
        k%=static_cast<int32_t>(data.size());
        if (k<0)
            k+=data.size();
        std::reverse(data.begin(),data.end());
        std::reverse(data.begin(),data.begin()+k);
        std::reverse(data.begin()+k,data.end());
    }
};

int main(){
    std::vector<int> data{1,2,3,4,5,6,7,8,9,10};
    Solution sol;
    sol.circularShift(data,-17);
    for (const auto &x:data)
        std::cout<<x<<" ";
    std::cout<<std::endl;
}