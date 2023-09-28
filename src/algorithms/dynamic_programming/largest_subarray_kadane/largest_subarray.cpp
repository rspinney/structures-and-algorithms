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

Largest Subarray - Kadane's algorithm

given an array of number, find the largest contiguous partial sum that is contained
within it

I.e. given [a,b,c,d,e,f]

a contiguious partial sum could be b+c+d, but not a+c+d

Naive: just test everything - requires 2 loops - O(n^2)
Efficient: dynamic programming using Kadane's algo - O(n)

Approach is iterative. Define a "useful quantity" for n+1 in terms of the answer for n

The "useful quantity" is the largest sum ending at index n, i.e.

largest_sum_at_j = max_i \sum_{j=i}^n data[j-1]

Given largest_sum_at_j for array 0:j-1, then largest_sum_at_j
for 1:j can  either be 'largest_sum_at_j + data[j]' or '0'
with the latter occuring if data[j] < 0, i.e. it is largest for 
i = j+1.

As we loop we can then keep track of the largest of such subarrays 
which finish at j to find the maximum. We can then also update the indices 
of the maxium subarray.

*/

#include <iostream>
#include <list>
#include <string>
#include "random.hpp"

using namespace structures_and_algorithms::random;

struct SubArray
{
    int32_t val;
    size_t start,end;
};

SubArray naive(const std::vector<int32_t> &data) //O(n^2)
{
    int32_t maxSum = - std::pow(2,31);
    size_t start = -1, end = -1;
    for (size_t i=0;i<data.size();++i){
        int32_t sum = 0;
        for (size_t j=i;j<data.size();++j){
            sum += data[j];
            if (sum > maxSum){
                maxSum = sum;
                start = i;
                end = j;
            }
        }
    }
    return {maxSum,start,end};
}

SubArray kaldane(const std::vector<int32_t> &data) //O(n)
{
    int32_t maxSum = - std::pow(2,31);
    int32_t maxSumN = 0;
    size_t start = 0, maxStart = 0, maxEnd = 0;
    for (size_t i=0;i<data.size();++i){
        if (maxSumN+data[i] >= 0){ //if the largest partial sum+data[i] >=0 the addition is current largest partial sum
            maxSumN += data[i];    // start index is retained
        }
        else{
            maxSumN = 0; //if not the largest partial is empty and the start point for the next partial sum is the next element
            start = i+1;
        }
    
        if (maxSumN > maxSum){ //check if we have the largest of such partial sums
            maxSum = maxSumN; 
            maxStart = start; //if so we record the value + start and end points
            maxEnd = i;
        }
    }
    return {maxSum,maxStart,maxEnd};
}

int main(/*int argc, char* argv[]*/)
{
    //set up data

    const int32_t M = 10;
    const size_t N = 20;
    RndUniform rnd;
    std::vector<int32_t> data;
    for (size_t i=0;i<N;++i)
        data.push_back(M*(2*rnd()-1));

    //////////////////////
    std::cout<<std::endl<<"Naive:"<<std::endl;
    SubArray result = naive(data);
    std::cout<<"data:"<<std::endl;
    int32_t test = 0;
    for (const auto &x:data)
        std::cout<<x<<" ";
    std::cout<<std::endl;
    std::cout<<"result: "<<result.val<<std::endl;    
    for (size_t i=result.start;i<=result.end;++i){
        std::cout<<data[i]<<" ";
        test += data[i];
    }
    std::cout<<std::endl;
    std::cout<<"subarray: "<<test<<std::endl;

    //////////////////////
    std::cout<<std::endl<<"Kaldane:"<<std::endl;
    result = kaldane(data);
    test = 0;
    std::cout<<"data:"<<std::endl;
    for (const auto &x:data)
        std::cout<<x<<" ";
    std::cout<<std::endl;
    std::cout<<"result: "<<result.val<<std::endl;    
    for (size_t i=result.start;i<=result.end;++i){
        std::cout<<data[i]<<" ";
        test += data[i];
    }
    std::cout<<std::endl;
    std::cout<<"subarray: "<<test<<std::endl;

    return 0;
}
