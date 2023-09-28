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

Binary Search - NON Recursive

Input: Sorted array/vector, value
Output: index of value in sorted array

Time: O(log(n))
Space: O(1)

*/

#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    //key value(s) to be found
    std::vector<int32_t> keys = {4,10,50,51,765,800};
    if(argc>1) keys = {atoi(argv[1])};
    //data - needs to be sorted
    const std::vector<int32_t> data = {10,20,34,50,100,230,343,765};

    for (const auto &key:keys){
        //index of key - to be updated if found
        int32_t index = -1;
        //left index - must be signed integer
        int32_t start = 0;
        //right index - must be signed integer
        int32_t end = data.size()-1;
        // while length of sub-array to be searched >=1
        while (start<=end){
            const int32_t mid = start +(end - start)/2; //written to avoid possible overflow from "start+end"
            if (data[mid]==key){ // if midpoint is key - end serch
                index= mid;
                break;
            }
            // if key > mid search upper remaining array
            if (data[mid]<key){
                start = mid + 1;
            }
            // ig key < mid search lower remaining array
            else{
                end = mid - 1;
            }
        }

        if (index<0){
            std::cout<<"Entry "<<key<<" not found"<<std::endl;
        }
        else{
            std::cout<<"Entry "<<key<<" found at index "<<index<<std::endl;
        }
    }

    return 0;
}