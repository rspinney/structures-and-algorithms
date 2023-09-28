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

//climbing stairs
//fibonacci sequence

class Solution {
public:
    int climbStairs(int n) {
        int last1=1,last2=0; //fibonacci initial condition
        for (int i=0;i<n;++i){
            int sum = last1+ last2;
            last2 = last1;
            last1 = sum;
        }
        return last1;
    }
};

//recusrive

class Solution {
public:
    int climbStairs(int n) {
        if (n<2)
            return 1;
        else
            return climbStairs(n-1)+climbStairs(n-2);
    }
};