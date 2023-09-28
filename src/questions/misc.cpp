
#include<iostream>
#include<vector>
#include <limits.h>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<stack>


//halfway there solution
class Solution1 {
public:
    double findMedianSortedArrays(std::vector<int>&& nums1, std::vector<int>&& nums2) {
             
        if (nums1.size()>nums2.size())
            std::swap(nums1,nums2);

        int n1= nums1.size();
        int n2= nums2.size();            
        bool found = false;
        
        int n = n1+n2;
        int isOdd = n%2;
        int medPos = (n1+n2+1)/2;
        int i=(n1)/2;
        int j=medPos-i;
        int l1,l2,r1,r2;
        while (!found){
            l1 = (i==0) ? INT_MIN:nums1[i-1];
            r1 = (i==n1) ? INT_MAX:nums1[i];
            l2 = (j==0) ? INT_MIN:nums2[j-1];
            r2 = (j==n2) ? INT_MAX:nums2[j];
            std::cout<<i<<" "<<j<<std::endl;
            std::cout<<l1<<" "<<l2<<" "<<r1<<" "<<r2<<std::endl;
            if ((r1>=l2)&&(r2>=l1)){
                found = true;
            }
            else if(l2>r1){
                --j;
                ++i;
            }
            else{
                --i;
                ++j;
            }
        }
        
        if (isOdd)
            return std::max(l1,l2);
        return 0.5*(std::max(l1,l2)+std::min(r1,r2));
    }
};

// //full binary search solution with O(log(m+n)) complexity
// class Solution {
//     double median(std::vector<int> &nums){
//         int n=nums.size();
//         int isodd = n%2;
//         if (isodd) return nums[(n)/2];
//         return 0.5*(nums[n/2]+nums[(n-1)/2]);
//     }
// public:
//     double findMedianSortedArrays(std::vector<int>&& nums1, std::vector<int>&& nums2) {
             
//         if (nums1.size()>nums2.size())
//             std::swap(nums1,nums2);

//         if (nums2.size()==0)
//             return median(nums1);

        
//         int n1= nums1.size();
//         int n2= nums2.size();            
        
//         int n = n1+n2;
//         int isOdd = n%2;
//         int medPos = (n1+n2+1)/2;
//         int l1,l2,r1,r2;
//         int min1 = 0, max1 = n1;
//         while (max1>=min1){
//             int pivot=(max1+min1)/2;
//             int slack=medPos-pivot;

//             l1 = (pivot==0) ? INT_MIN:nums1[pivot-1];
//             r1 = (pivot==n1) ? INT_MAX:nums1[pivot];
//             l2 = (slack==0) ? INT_MIN:nums2[slack-1];
//             r2 = (slack==n2) ? INT_MAX:nums2[slack];
    
//             if ((r1>=l2)&&(r2>=l1)){
//                 if (isOdd)
//                     return std::max(l1,l2);
//                 return 0.5*(std::max(l1,l2)+std::min(r1,r2));
//             }
//             else if(l2>r1){
//                 min1 = pivot+1;
//             }
//             else{// if(l1>r2){
//                 max1 = pivot-1;
//             }
//         }
//         return 0.0;
//     }
// };
// int main(){
//     Solution sol;
//     std::cout<<sol.findMedianSortedArrays({1,3},{2})<<std::endl;
//     return 0;
// }

class Solution {
    inline int expand(int i1,int i2,const std::string &s)const{
        int k=0,kk=-1;
        while (((i1-k)>=0)&&( (i2+k)<s.length())){
            if (s[i1-k]==s[i2+k]){
                kk=k;
            }
            else{
                break;
            }
            ++k;
        }
        return kk;
    }
public:
    std::string longestPalindrome(std::string &&s)const {

        int n = s.length();
        if (n<2)return s;
        std::string ss =s;
        std::reverse(ss.begin(),ss.end());
        if (ss==s) return s;
        
        int start = 0,len = 0;
        for (int i=0;i<n;++i){
            int k1 = expand(i,i,s);
            int k2 = expand(i,i+1,s);

            if ((2*k1)>len){
                start= i-k1;
                len=2*k1;
            }
            if ((2*k2+1)>len){
                start= i-k2;
                len=2*k2+1;
            }
        }
        return s.substr(start,len+1);
    }
};

int main(){
    Solution sol;
    std::cout<<sol.longestPalindrome("babad")<<std::endl;
    return 0;
}