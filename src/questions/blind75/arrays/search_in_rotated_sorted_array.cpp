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

//search for target in rotated sorted array

//binary search with annougin accounting for all corner cases

class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        int l=0,u=nums.size()-1;
        int m=l+(u-l)/2;
        if (nums[m]==target)
                return m;
        while (l<u){
            
            if ((nums[m]<=target)&&(nums[u]>=target)){
                l = m+1;
            }
            else if ((nums[m]>=target)&&(nums[l]<=target)){
                u = m-1;
            }
            else if ((nums[m]>=target)&&(nums[l]>=target)){
                if (nums[m]>=nums[l])
                    l=m+1;
                else
                    u=m-1;
            }
            else if ((nums[m]<=target)&&(nums[u]<=target)){
                if (nums[m]<=nums[u])
                    u=m-1;
                else
                    l=m+1;
            }
            m=l+(u-l)/2;
            if (nums[m]==target)
                return m;
        }
        return -1;
    }
};