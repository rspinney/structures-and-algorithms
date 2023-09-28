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
return division of dividend/divisor without using * / or %

*/

#include <iostream>
#include <limits.h>

//division (rounded down) without suing * % or /

class Solution {
public:
    int divide(int dividend, int divisor) {
        //edge cases
        if(dividend== INT_MIN && divisor== 1) return INT_MIN;
        if(dividend== INT_MIN && divisor== -1) return INT_MAX;
        
        //sign of result
        int sgna = (dividend>0) ? 1 : -1;
        int sgnb = (divisor>0) ? 1 : -1;
        int sgn = sgna * sgnb;
        
        //work with absolute values
        int64_t a=abs(dividend);
        int64_t b=abs(divisor);
    
        //running number of times b fits in a
        int64_t k=0;
        
        while (a>=b){ // we remove b from a until it doesnt fit
            int p = 1;
            long int tot = b;
            //we dont remove b one by one, but try adding largest powers of 2 to a total
            // specifically: add b^(2n) each time
            while (a-tot >= tot){//if tot + next power of 2 fits
                tot+=tot;
                p+=p; //p = number of a in total
            }
            a-=tot;
            k+=p;
        }
                
        if (sgn>0)
            return k;
        return -k;
    }
};


int main(){
    Solution sol;    
    std::cout<<sol.divide(126,5)<<std::endl;
}