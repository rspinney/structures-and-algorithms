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

Recursive Binary Search

Input: Sorted array/vector, value
Output: index of value in sorted array

Time: O(log(n))
Space: O(log(n))

Notes: general concerns about recursion - space complexity due to number of stack frames

*/

#include <iostream>
#include <vector>

int32_t binary_search(
                    const std::vector<int32_t> &data, //data to be searched
                    const int32_t start, //left index of searching region
                    const int32_t end, //right index of searching region
                    const int32_t key //value to be searched for
){
    //optional:
    //if ((data[start]>val)||(data[end]<val)) return -1;

    //if indices cross we have fully searched and the key is not in the array
    if (end<start) return -1; //note: indicies must be signed integers to detect end = 0, start = -1 edge case
    // calculate midpoint
    const int32_t mid = start + (end-start)/2; //written to avoid possible overflow from "start+end"
    // check if midpoint is key, if so return index
    if (data[mid]==key) return mid;
    // search remaining right part of array if key > midpoint
    else if (data[mid] > key) return binary_search(data,start,mid-1,key);
    // search remaining left part of array if key < midpoint
    else return binary_search(data,mid+1,end,key);
}

int main(int argc, char* argv[])
{
    //key value(s) to be found
    std::vector<int32_t> keys = {4,10,50,51,765,800};
    if(argc>1) keys = {atoi(argv[1])};
    // data: needs to be sorted
    const std::vector<int32_t> data = {10,20,34,50,100,230,343,765};
    for (const auto &key:keys){
        //call to recursive function
        int32_t index = binary_search(
                                    data, //data
                                    0, //left index of search
                                    data.size()-1, //right index of search
                                    key //value to be found
                                    );

        if (index<0){
            std::cout<<"Entry "<<key<<"  not found"<<std::endl;
        }
        else{
            std::cout<<"Entry "<<key<<" found at index "<<index<<std::endl;
        }
    }
    return 0;
}