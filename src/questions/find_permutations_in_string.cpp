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
given a vector of equal length strings = words
and a string s

find all the instances of substings in s that are exact permutations of words
by return a vector of all starting indices

e.g. words = {ab,cd,de}
s = {mjdecdabqw}

return {2}

*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>


class Solution {
public:
  
    std::vector<int> findSubstring(const std::string &s, std::vector<std::string>& words) {
        
        std::vector<int> found; //what we will return        
        std::unordered_map<std::string,int> m; //count number of different words in a permutation

        for (size_t i=0;i<words.size();++i){
            if (m.count(words[i])){
                m[words[i]]++;
            }
            else{
                m[words[i]]=1;
            }
        }
        
        //maximum length that we need to test
        size_t l= s.length() - words.size()*words[0].length() + 1;
        
        //run through string
        for (size_t i=0;i<l;++i){
            //get first word long substr
            std::string ss = s.substr(i,words[0].length());
            //is a word?
            if (m.count(ss)){//we have a match
                //count next words
                std::unordered_map<std::string,int> mm;
                //starting pos
                size_t start = i;
                size_t found_words = 0;
                bool isconcat = true;
                //until end of string
                while (start < s.length() - words[0].length() + 1)
                {   
                    //find  substr (includes first one)
                    std::string sss = s.substr(start,words[0].length());
                    
                    if (!m.count(sss)) //not a word
                        break;

                    if (!mm.count(sss)) //put placeholder in temp map
                        mm[sss]=0;

                    found_words++; //word found +1
                    mm[sss]++; //count the word in the new map

                    if (mm[sss]>m[sss]){ //word appears too many times - greater than original map of permutation
                        isconcat = false;
                        break;
                    }

                    if (found_words==words.size())//got to needed length
                        break;

                    start+=sss.length(); //next position in string
                }
                if ((isconcat)&&(found_words==words.size())) //we have a permutation
                    found.push_back(i);
            }
        }
        return found;   
    }
};


int main(){
    Solution sol;  
    std::string s = "asffrabcddepel";
    std::vector<std::string> words;
    words.push_back("ab");
    words.push_back("cd");
    words.push_back("de");
    auto ans=sol.findSubstring(s,words);
    for (const auto &x:ans)
        std::cout<<x<<" ";
    std::cout<<std::endl;
}