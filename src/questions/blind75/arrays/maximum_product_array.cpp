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


#include<iostream>
#include<vector>
#include <limits.h>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<stack>

//maximum product array

class Solution {
public:
    int maxProduct(std::vector<int>& nums) {
        int maxProd = nums[0];
        int maxPos = std::max(0,nums[0]);
        int maxNeg = std::min(0,nums[0]);
        for (int i=1;i<nums.size();++i){   
            int x = nums[i];
            if (x<0) std::swap(maxPos,maxNeg);
            // maxPos = max(x,x*maxPos);
            // maxNeg = min(x,x*maxNeg);
            maxPos = x*maxPos;
            maxNeg = x*maxNeg;
            if (!maxPos)
                maxPos = std::max(0,x);
            if (!maxNeg)
                maxNeg = std::min(0,x);
            maxProd = std::max(maxPos,maxProd);
        }
        return maxProd;
    }
};