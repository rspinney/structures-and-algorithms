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
Given string of ( and )

find the length of the longest valid sequence of matched brackets
e.g.

((()()(())()(

return 10

*/

#include <iostream>
#include <string>
#include <stack>

/* use a stack to push and pop matched brackets */

class Solution {
public:
    int longestValidParentheses(std::string &s) {
        //we store positions of unmatched (
        std::stack<int> st;
        //we need a previous one to act as backmarker, start at 0 so backmarker at -1
        st.push(-1);//initial backstop - dummy unmatched (
        //if followed by perfectly matched ()'s then this is the origin position
        int maxlen=0;
        for (size_t i=0;i<s.length();++i){
            if (s[i] =='('){
                st.push(i);//new start
            }
            else{
                st.pop();//remove matched closed (
                if (st.empty()){
                    st.push(i); //new dummy unmatched (
                }
                else{
                    //new length is position - last unmatched (
                    maxlen=std::max(maxlen,static_cast<int>(i)-st.top());
                }
            }       
        }
        return maxlen;
    }
};

int main(){
    Solution sol;  
    std::string s = "((()()(())()(";
    std::cout<<sol.longestValidParentheses(s)<<std::endl;
}