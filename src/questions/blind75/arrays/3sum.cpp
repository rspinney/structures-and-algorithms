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


//THREE SUM

//naive

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::sort(nums.begin(),nums.end());
        std::vector<std::vector<int> > ans;
        std::unordered_set<int> Start;
        for (int i=0;i<nums.size();++i){
            if (!Start.count(nums[i])){
                
                std::unordered_set<int> Pair;
                std::unordered_set<int> used;
                for (int j=i+1;j<nums.size();++j){
                    if ((Pair.count(-nums[j]))&&(!used.count(-nums[j]))){
                        //found
                        ans.push_back({nums[i],-nums[i]-nums[j],nums[j]});
                        used.insert(-nums[j]);
                        
                    }
       
                    Pair.insert(nums[i]+nums[j]);            
                }
            }
            Start.insert(nums[i]);
        }        
        return ans;
    }
};

//soln

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<std::vector<int>> ans;
        
        std::sort(nums.begin(), nums.end());
        for(int i=0; i<nums.size(); i++){
            if(i >= 1 && nums[i] == nums[i-1]) continue;
            
            int left = i+1;
            int right = nums.size()-1;
            
            while(left < right){
                int sum = nums[left] + nums[i] + nums[right];
                
                if(sum > 0){
                    right--; continue;
                }
                
                if(sum < 0){
                    left++; continue;
                }
                
                if(sum == 0){
                    std::vector<int> tmp= {nums[i],nums[left],nums[right]};
                    ans.push_back(tmp);
                    
                    while( left < right && nums[left] == nums[left+1] ) left++;
                    while( left < right && nums[right] == nums[right-1]) right--;
                }
                
                left++, right--;
            }
        }
      
        return ans;
    }
};