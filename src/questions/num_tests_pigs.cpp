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

here are buckets buckets of liquid, where exactly one of the buckets is poisonous. To figure out which one is poisonous, you feed some number of (poor) pigs the liquid to see whether they will die or not. Unfortunately, you only have minutesToTest minutes to determine which bucket is poisonous.

You can feed the pigs according to these steps:

    Choose some live pigs to feed.
    For each pig, choose which buckets to feed it. The pig will consume all the chosen buckets simultaneously and will take no time. Each pig can feed from any number of buckets, and each bucket can be fed from by any number of pigs.
    Wait for minutesToDie minutes. You may not feed any other pigs during this time.
    After minutesToDie minutes have passed, any pigs that have been fed the poisonous bucket will die, and all others will survive.
    Repeat this process until you run out of time.

Given buckets, minutesToDie, and minutesToTest, return the minimum number of pigs needed to figure out which bucket is poisonous within the allotted time.

see explanation pdf
*/

#include <iostream>
#include <math.h>  

#define EPS 0.0001
class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
     
        int tests = (minutesToTest / minutesToDie);
        
       return std::ceil(-EPS+log(buckets)/log(tests+1));
    }
};

int main(){
    
    Solution sol;
    int ans  = sol.poorPigs(1000,15,60);
    std::cout<<ans<<std::endl;
}