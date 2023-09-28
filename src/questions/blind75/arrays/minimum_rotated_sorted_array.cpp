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

//minimum in rotated sorted array

//binary search

class Solution {
public:
    int findMin(std::vector<int>& nums) {
        int l = 0;
        int u = nums.size()-1;
        int m = (u+l)/2;
        while (nums[l]>nums[u]){
           // std::cout<<l<<" "<<m<<" "<<u<<std::endl;
            if (nums[m]<nums[l]){
                u=m;
            }
            else{
                l=m+1;
            }
            m=(u+l)/2;
            //std::cout<<l<<" "<<m<<" "<<u<<std::endl;
        }
        return nums[l];
    }
};