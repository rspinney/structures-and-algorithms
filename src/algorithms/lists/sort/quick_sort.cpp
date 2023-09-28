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

Quick sort

Average performance O(n*log(n))

1. set up function "partition" operating on [low,high] which moves the last value into the correct position, with
    all values before it with having values less than it, and all above greater than it
    e.g. [2,4,1,3,8,7,5] -> [2,4,1,3,5,8,7]
    The value in the correct position is called the "pivot", here it is 5 in index 4.
2. Call the function on the array before the pivot
    e.g. on [2,4,1,3] (which would give [2,1,3,4] with pivot = 4 in index 2)
3. Call the function on the array after the pivot
    e.g. on [8,7] (which would give [7,8] with pivot = 7 in index 0)

Calling on lists gives two obvious options:
1. move nodes around by moving the data (easy)
2. move nodes around by literally reorgansing the list through the pointers to nodes (harder)

We implement them through two different parition functions, "parition" and "partitionPtr", respectively

General efficiency constraints: limit O(n) calls to find pointers like find(*ptr) which search through the whole list where possible
Doesn't *really* matter as whole algorithm is O(n*log(n)) expected 

In both, because we can only iterate forward we thus want to return the pointer to the node *BEFORE* the pivot from
the pivot function

In option 2. the above is harder as exchanging nodes exchanges the order of pointers in inconsistent ways when iterating through a list
In particular it behaves differently if you are swapping immediate neighbours or not. This requires explicit compensation.
*/

#include <iostream>
#include <queue>
#include "list.hpp"
#include "random.hpp"
#include "comparators.hpp"

using namespace structures_and_algorithms::structures::lists;
using namespace structures_and_algorithms::random;
using namespace structures_and_algorithms::comparators;

template<typename T>
class ListSort : public List<T>{
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
    //version that swaps data - O(high-low)
    template<typename func>
    ptr* partition(const ptr* low,const ptr* high, const func &compare)
    {
        T pivot = (*high)->data;
        ptr *tailPtr = low; //this ptr is now end of the "less than" part *exclusive* - i.e. it need to be used
        ptr *pivotPrevPtr = nullptr; //this is the pointer to BEFORE the final pivot point
        ptr *p = low;
        while ((*p)&&(p != high)){
            if (compare((*p)->data, pivot)){
                pivotPrevPtr = tailPtr;
                swap((*p)->data,(*tailPtr)->data); //move data to the end of the "less than" part
                tailPtr = &(*tailPtr)->next; //increment end of the "less than" part
            }
            p = &((*p)->next); //iterate
        }

        swap((*high)->data,(*tailPtr)->data); //move the pivot data into the "less than" part
        return pivotPrevPtr; //return the node before the pivot index
    }

    //version that swaps the nodes themselves (complicated!) - O(high - low)
    template<typename func>
    ptr* partitionPtr(const ptr* low,ptr* &high, const func &compare) //note  side effects in high - we must update it appropriately
    { 
        T pivot = (*high)->data;
        ptr *tailPtr = const_cast<ptr*>(low); //this ptr is now end of the "less than" part *exclusive* - i.e. it need to be used
        ptr *pivotPrevPtr = nullptr; //this is the pointer to BEFORE the final pivot point - we initially do not know prev of low - set to null
        ptr *p = const_cast<ptr*>(low); //start of iteration through partition
        //ptrs are not stable, we have to identify end point with where it goes on to point to before it might get modified
        ptr *highNext = &(*high)->next; 

        while ((*p) && (&(*p)->next != highNext)){ //sweep through parititon
            if (compare((*p)->data, pivot)){//if less than the pivot value move it to the front
                //keep track of end pointer to one before end of "less than" section
                pivotPrevPtr = tailPtr; 
                // we need to find the next iteration point (as after swap) "before" we swap - ptrs not in order afterwards
                ptr *pNext  = &(*tailPtr)->next;  //pointer to next p after swap
                ptr *tailPtrNext = &(*p)->next;  //pointer to nect tailPtr after swap
                //swap them - move data to the end of the "less than" part
                swap(*p,*tailPtr); 
                //iterate after swap
                p       = pNext; 
                tailPtr = tailPtrNext;
            }
            else{
                p = &((*p)->next); //iterate regularly
            }
        }
        //we have exited when we have reached the final pointer in the partition - set high to this value
        high = p; // <--- side effects here
        //quirk of swapping pointers in list:
        //1. if not consecutive - pointers to data get cleanly swapped, so high still points at the last member in partition
        //2. if consecutive - high no longer points to high as pointers AND subsequent pointers are swapped
        //3. so detect case 2 and in that case we can find "high" as the "next" pointer from the swapped node
        bool neighbour = (&(*tailPtr)->next == high ) ? true : false; // last swap in between consecutive nodes - can't rely on pointers
        swap(*high,*tailPtr); //move the pivot data into position
        if (neighbour) high = &(*tailPtr)->next; //< -- side effects here
        return pivotPrevPtr; //return the node *before* the pivot index - returns nullptr if pivot = low
    }

    ///////////////// RECURSIVE /////////////////////////

    //recursive function 
    template<typename func>
    void quickSort(ptr *low, ptr *high, const func &compare)
    {
        //ptr *low = a_low, *high = a_high; // to deal with updating bounds when changing pointers
        if ((*low == *high)||(!*low)||(!*high))
            return;
            //see iterative version for details
        ptr *pivotPrevPtr = partitionPtr(low,high,compare); // rearranges data and causes element at pivotIndex to be in the right place
        ptr *pivot = (pivotPrevPtr) ? &(*pivotPrevPtr)->next : low; // if pivotPrevptr is null then it is not in [low,high], so low is pivot
        if ((*low)&&(pivotPrevPtr))
            quickSort(low,pivotPrevPtr,compare); //lower remaining half
        if ((*high)&&(&((*pivot)->next)))
            if (pivot != high) // possible to overlap bounds - check
                quickSort(&((*pivot)->next),high,compare); // upper remaining half 
    }

public:
    //ctors
    ListSort():List<T>(){}
    ListSort(std::vector<T> &data):List<T>(data){}

    // RECURSIVE ENTRY POINT //

    template<typename func = decltype(lessThan<T>)>
    void quickSort(const func compare = lessThan<T>)
    {
        quickSort(&(this->root),lastPtr(),compare);
    }

    ///////////////// ITERATIVE ///////////////////////

    template<typename func = decltype(lessThan<T>)>
    void quickSortIterative(const func compare = lessThan<T>)
    {
        // using queue for breadth first search - doesn't really matter
        std::queue<std::pair<ptr*,ptr*> > partitions;
        partitions.push({&(this->root),lastPtr()});
        while (!partitions.empty()){
            //get next partition 
            ptr *low = partitions.front().first;
            ptr *high = partitions.front().second;
            //remove it fromt the queue
            partitions.pop();
            //if there is more than one node in partition
            if (low != high){
                // puts pivot in correct place, returns ptr BEFORE pivot
                // if using partitionPtr(...):
                //  side effects on high to ensure it points to the
                //  same INDEX along the list (ptrs may have changed)
                ptr *pivotPrevPtr = partitionPtr(low,high,compare); 
                // if the previous point is nullptr it is not in [low,high], therefore pivot = low
                ptr *pivot = (pivotPrevPtr) ? &(*pivotPrevPtr)->next : low; 

                if ((*low)&&(pivotPrevPtr))
                    partitions.push({low,pivotPrevPtr}); // add the current list section before the pivot point
                
                if ((*high)&&((*pivot)->next))
                    if (pivot != high) // possible to overlap bounds - check
                        partitions.push({&(*pivot)->next,high});  // add the current list section after the pivot point
            }
        }
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
    const size_t N=10;
    const T M=100;
    RndUniform rnd;
   
    uint32_t count =  0, max_count = 100;

    while (count<max_count){
        std::cout<<std::endl<<std::endl<<"!!!!!!!!!!!NEW LIST!!!!!!!!!!!!!!!!!"<<std::endl<<std::endl;
        ListSort<T> listI{};
        for (size_t i=0;i<N;i++)
            listI.push_front(M*(2.0*rnd()-1.0));
        listI.quickSort();
        
        if (!listI.checkSorted()){   
            std::cout<<"not sorted! "<<count<<std::endl;
            listI.print();
            break;
        }
        else{
            std::cout<<"sorted! "<<count<<std::endl;
            listI.print();
        }

        std::cout<<std::endl<<std::endl<<"!!!!!!!!!!!NEW LIST!!!!!!!!!!!!!!!!!"<<std::endl<<std::endl;
        ListSort<T> list{};
        for (size_t i=0;i<N;i++)
            list.push_front(M*(2.0*rnd()-1.0));
        list.quickSortIterative(greaterThan<T>);
        
        if (!list.checkSorted(greaterThan<T>)){   
            std::cout<<"not sorted! "<<count<<std::endl;
            list.print();
            break;
        }
        else{
            std::cout<<"sorted! "<<count<<std::endl;
            list.print();
        }
        ++count;
    }

    return 0;
}