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

Merge sort

Average performance O(n*log(n))

1. Consider the array as a sequnce of 2^n sub-arrays
2. Starting with lowest nontrivial length subarray = 2
3. merge the two constituent, already sorted, subarrays (initially of length 1)
   into a single sorted subarray
4. double the sub array length which then deals with two longer sorted subarrays

Can be done recursively through recursive function mergeSort which calls 
mergeSort on the subarrays *then* merges the results

Or can be done iteratively in which we start at subarray length 1 and then merge
and double the sub-array length until we have sorted the whole array

We use a merge function which inserts in-place as that is now efficient for a list.
It does it my changing links between the nodes, not the data.
*/

#include <iostream>
#include "list.hpp"
#include "random.hpp"
#include "comparators.hpp"

using namespace structures_and_algorithms::structures::lists;
using namespace structures_and_algorithms::random;
using namespace structures_and_algorithms::comparators;

template<typename T>
class MergeSort : public List<T>{
    typedef typename List<T>::Node Node; // nested class Node in List is now dependent type
    typedef std::unique_ptr<Node > ptr; //save us writing it out...
    
    //retrive the last pointer in the list - O(n)
    ptr *lastPtr() const
    {
        ptr *p = const_cast<ptr*>(&this->root);
        while ((*p)&&((*p)->next)){
            p = &((*p)->next);
        }
        return p;
    }

    ptr *lastPtr(ptr *p) const
    {
        while ((*p)&&((*p)->next)){
            p = &((*p)->next);
        }
        return p;
    }

    //swap the nodes through pointer moves - O(1)
    void swap(ptr &a,ptr &b) const
    {
        if (a==b)
            return;
        if (a && b){
            
            ptr temp = std::move(b);
            b = std::move(a);
            a = std::move(temp);

            // need to get references to them now (before they might be altered) 
            // as b->next might equal a or vice versa
            ptr & aNext = a->next; 
            ptr & bNext = b->next;

            temp = std::move(bNext);
            bNext = std::move(aNext);
            aNext = std::move(temp);
        }
    }

    //swap the data values - O(1)
    void swap(T &a, T &b) const // this is basically std::swap(a,b);
    {
        T temp = std::move(a);
        a = std::move(b);
        b = std::move(temp);
    }
    
    //we merge by removing and inserting nodes in the two lists before combining them
    // this is the same form as "mergeInPlace" for the array version, but is now efficient for lists
    template<typename func>
    void merge(ptr *left, ptr *right, const func &compare)
    {
        ptr *lastLeft = lastPtr(left); //end node of left list
        ptr &leftTail = (*lastLeft)->next; //ref to the dangling link of left list
        ptr *i = left, *j = right; //start nodes for each subarray
 
        if ((!(*j)) || (!compare((*j)->data,(*lastLeft)->data))){//already merged
            leftTail = std::move(*right); //stick them together
            return;
        }
 
        while (1){//whilst BOTH are in bounds
            if (compare((*i)->data,(*j)->data)){ // data at *i is in correct position, increment i
                if (!(*i)->next) // OOB
                    break;
                i = &(*i)->next;   
            }
            else{ // we need to move data in j to i and move displaced data one to the righ
                //remove node at j
                ptr jval = std::move(*j);
                *j = std::move(jval->next); //j auto iterates
                //insert node 
                ptr next = std::move(*i); //hold the remainder of the list from this point
                (*i) = std::move(jval); //insert the node in the current ptr location
                (*i)->next = std::move(next); //move the remainder into place
                if ((!(*i)->next)||(!(*j))) //OOB
                    break;
                //increment i one to the right
                i = &(*i)->next;
            }   
        }
        leftTail = std::move(*right); //stick them together
    }

    //iterates two points, one a half speed, in order to find midpoint.
    ptr *findMid(ptr *start){
        ptr *pi = start;
        ptr *pj = start;
        while(*pi){
            pi = &(*pi)->next;
            if (*pi){
                pi = &(*pi)->next;
                pj = &(*pj)->next;
            }
        }
        return pj;
    }

    ///////////////// RECURSIVE /////////////////////////

    template<typename func>
    void mergeSort(ptr *low, const func &compare)
    {
        if (!(*low)->next)
            return;
        ptr *mid = findMid(low);

        ptr right = std::move(*mid); //split the list - assumes we have been passed a split list - no need for "ptr *high"
        ptr left = std::move(*low);

        mergeSort(&left,compare); //lower half
        mergeSort(&right,compare); // upper half
        merge(&left,&right,compare); // after two lower halfs sorted, merge the two sections
        
        *low = std::move(left);
    }

public:
    //ctors
    MergeSort():List<T>(){}
    MergeSort(std::vector<T> &data):List<T>(data){}

    // RECURSIVE ENTRY POINT //
    template<typename func = decltype(lessThan<T>)>
    void mergeSort(const func compare = lessThan<T>){
        mergeSort(&this->root,compare);
    }

    ///////////////// ITERATIVE ///////////////////////

    template<typename func = decltype(lessThan<T>)>
    void mergeSortIterative(const func compare = lessThan<T>)
    {
        size_t n = this->sizeExplicit();
        std::vector<ptr> ptrs(n);
        ptr *p = &this->root;
        for (auto &x:ptrs){ //populate array with all smallest sub-lists - single elements
            x = std::move(*p);
            p = &(x)->next;
        }

        size_t partitionLength = 1; // length of initial list
        while (partitionLength < n){ //whilst the partition length is a subList
            size_t index = 0;
            while (index < n -  partitionLength){ // iterate through the sub-lists
                merge(&ptrs[index],&ptrs[index+partitionLength],compare);//merge pairs of sub-lists
                index += 2*partitionLength; //iterate through pairs
            }
            partitionLength *= 2; //double the partition length
        }
        this->root = std::move(ptrs[0]);//list is now at ptrs[0] , move back to list
    }

    //confirm sorted list - O(n)
    template<typename func = decltype(lessThan<T>)>
    bool checkSorted(const func compare = lessThan<T>) const
    {
        ptr *p = const_cast<ptr*>(&this->root);
        ptr *pNext = p;
        while (*p){
            pNext=&((*p)->next);
            if ((*pNext)&&(compare((*pNext)->data,(*p)->data)))
                return false;
            p = pNext;
        }
        return true;
    }
};

int main(/*int argc, char* argv[]*/)
{   
    typedef int32_t T;
    const T M=100;
    RndUniform rnd;
   
    uint32_t count =  0, max_count = 100, errors = 0;

    while (count<max_count){

        const size_t N = 10 * (1 + rnd()); //try for different data lengths

        //recursive version, low to high
        std::cout<<std::endl<<std::endl<<"!!!!!!!!!!!NEW LIST!!!!!!!!!!!!!!!!!"<<std::endl<<std::endl;

        MergeSort<T> listI{};
        for (size_t i=0;i<N;i++)
            listI.push_front(M*(2.0*rnd()-1.0));
        
        std::cout<<"unsorted"<<std::endl;
        listI.print();
        std::cout<<std::endl;
        listI.mergeSort();
        
        

        if (!listI.checkSorted()){   
            std::cout<<"not sorted! "<<count<<std::endl;
            listI.print();
            ++errors;
            break;
        }
        else{
            std::cout<<"sorted! "<<count<<std::endl;
            listI.print();
        }

        //iterative verion, high to low

        std::cout<<std::endl<<std::endl<<"!!!!!!!!!!!NEW LIST!!!!!!!!!!!!!!!!!"<<std::endl<<std::endl;
        MergeSort<T> list{};
        for (size_t i=0;i<N;i++)
            list.push_front(M*(2.0*rnd()-1.0));
        
        std::cout<<"unsorted"<<std::endl;
        listI.print();
        std::cout<<std::endl;
        list.mergeSortIterative(greaterThan<T>);
        
        if (!list.checkSorted(greaterThan<T>)){   
            std::cout<<"not sorted! "<<count<<std::endl;
            list.print();
            ++errors;
            break;
        }
        else{
            std::cout<<"sorted! "<<count<<std::endl;
            list.print();
        }
        ++count;
    }

    std::cout<<std::endl<<errors<<" errors in sorting"<<std::endl;

    return 0;
}