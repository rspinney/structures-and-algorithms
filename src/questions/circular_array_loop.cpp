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

You are playing a game involving a circular array of non-zero integers nums. 
Each nums[i] denotes the number of indices forward/backward you must move if you are located at index i:

    If nums[i] is positive, move nums[i] steps forward, and
    If nums[i] is negative, move nums[i] steps backward.

Since the array is circular, you may assume that moving forward from the last element puts you on the 
first element, and moving backwards from the first element puts you on the last element.

A cycle in the array consists of a sequence of indices seq of length k where:

    Following the movement rules above results in the repeating index sequence seq[0] -> seq[1] -> ... -> seq[k - 1] -> seq[0] -> ...
    Every nums[seq[j]] is either all positive or all negative.
    k > 1

Return true if there is a cycle in nums, or false otherwise.
*/

#include <iostream>
#include <vector>
#include <unordered_set>


//effectively DFS solution
class Solution {
    //function to get next position in array
    inline int next(std::vector<int>& nums,int i){
        int n = nums.size(); //v important to convert to int for -ve values to make mod operation work
        return (i+(nums[i]%n) + n) % n; //initial position +  deviation wrapped to  [-(n-1),n-1] + n to map wrap to [1,2n-1] then wrapped to [0,n-1]
    }
public:
    bool circularArrayLoop(std::vector<int>& nums) {
    
        if (nums.size() < 2) return false;
        //keep track of which sites we have tried loops from - never start from one we have looped to
        std::vector<bool> visited(nums.size(),false); //could be an unordered_set
            
        for (size_t i=0;i<nums.size();++i){ //all starting positions
            if (!visited[i]){ //if we havent visited
                size_t pos = i; //start
                size_t nextpos = next(nums,pos); //next
                
                std::unordered_set<int> set; //visited elements in this loop
                set.insert(pos);
                visited[pos]=true; //visited
                
                bool startdir = (nums[pos] > 0); //initial direction

                //whilst going in same direction and not mapping to same position (stopped moving)
                while(((nums[pos]>0)==startdir)&&(nextpos!=pos)){
                    if (set.find(nextpos)==set.end()){ //if next not found, add to structures, keep looping
                        set.insert(nextpos);
                        visited[nextpos]=true;
                        pos = nextpos;
                        nextpos = next(nums,nextpos);                        
                    }
                    else{                
                        return true; //found a loop
                    }
                }
            }
        }
        return false; //if we are here, no loops
        
    }
};

//racing pointers solution

//detect loops by having a fast iterator catch a slow iterator

class Solution1 {
public:
    bool circularArrayLoop(std::vector<int>& nums) {
        if (nums.size() < 2) return false;
        //keep track of which sites we have tried loops from - never start from one we have looped to
        std::vector<bool> visited(nums.size(),false); //could be an unordered_set
        for (size_t i = 0; i < nums.size(); i++) { //try all starting positions
            if (!visited[i]){
                size_t slow = i;
                size_t fast = i;
                int8_t dir = direction(nums, i); //which way are we going
                while(1) {
                    slow = next(nums, slow); //updated slow index
                    if (direction(nums, slow) != dir) break; //wrong direction
                    visited[slow]=true; //visited slow node
                    fast = next(nums, fast); //update fast index
                    if (direction(nums, fast) != dir) break;//wrong direction
                    fast = next(nums, fast);//update fast index again - hence "fast"
                    if (direction(nums, fast) != dir) break;//wrong direction
                    if (slow == fast) { //if fast catches slow we have a loop
                        if (next(nums, fast) == slow) {
                            break; //but if the next index is itself it is a trivial loop - doesn't count
                        }
                        return true; //loop if here
                    }
                }
            }
        }
        return false; //no loops found
    }
    inline int8_t direction(std::vector<int>& nums, size_t i) {
        return nums[i] > 0 ? 1 : -1;
    }
    inline size_t next(std::vector<int>& nums,size_t i){
        int n = nums.size(); //v important to convert to int for -ve values to make mod operation work
        return (i+(nums[i]%n) + n) % n; //initial position +  deviation wrapped to  [-(n-1),n-1] + n to map wrap to [1,2n-1] then wrapped to [0,n-1]
    }
};

int main(){
    std::vector<int> nums{-1,-2,-3,-4,-5};
    Solution sol;
    bool ans = sol.circularArrayLoop(nums);
    Solution sol1;
    bool ans1 = sol1.circularArrayLoop(nums);
    std::cout<<ans<<" "<<ans1<<std::endl;
}