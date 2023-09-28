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


// Best time to buy/sell

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        int lowest = prices[0];
        int maxprofit=0;
        for (auto &p:prices){
            lowest = std::min(lowest,p);
            maxprofit = std::max(maxprofit,p-lowest);
        }
        return maxprofit;
    }
};