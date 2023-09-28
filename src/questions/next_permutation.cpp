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
return the next lexicographical permutation of vector of ints.

e.g.

input : {4,5,3,1,6}

output : {4,5,3,6,1}

if given largest permutation e.g. {6,5,4,3,2,1}
return lowest, e.g. {1,2,3,4,5,6}
*/

#include <iostream>
#include <vector>
#include <algorithm>


// fundamentally exploits the fact that the end of the permutation to change will always be decreasing
// so find last increasing point and modify there
/*

e.g. {4,5,8,4,6,5,1}

We find (one before) the last increasing index i.e

e.g. {4,5,8,*4*,6,5,1}

We then find the smallest number after this, greater than this value
Note: because it is decreasing after this it is the last value larger than the found index

e.g. {4,5,8,*4*,6,*5*,1}

Swap these values

e.g. {4,5,8,*5*,6,*4*,1}

Reverse the array past the first index
Note, effectively same as sorting the remainder of the array

e.g. {4,5,8,*5*,1,*4*,6}

*/

class Solution {
public:
    void nextPermutation(std::vector<int>& nums) {
        int l=nums.size();
        int index1=0,index2=0;
        for(int i=l-2;i>=0;i--){
            if(nums[i]<nums[i+1]){ // last increasing index (one before)
                index1=i;
                break;
            }
        }
        if(index1<0){ // largest permutation, so reverse it
            std::reverse(nums.begin(),nums.end());
        }
        else{
            //find last valur larger
            for(int i=l-1;i>index1;i--){
                if(nums[i]>nums[index1]){
                    index2=i;
                    break;
                }
            }   
            //swap them
            std::swap(nums[index1],nums[index2]);
            //reverse the remainder
            std::reverse(nums.begin()+index1+1,nums.end());
        }
    }
};

int main(){
    Solution sol;  
    std::vector<int> data= {4,5,8,4,6,5,1};
    sol.nextPermutation(data);
    for (const auto &x:data)
        std::cout<<x<<" ";
    std::cout<<std::endl;
}