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

Bubble sort

Average performance O(n^2) - not an efficient sorting algorithm for real use

1. Loop over end point of a range from end of array to beginning
2. Nested loop from beginning to outer loop value
3. swap neighbours if not in order
4. result is largest in considered range is moved to the end
5. range shrinks until the whole array is sorted

Calling on lists gives two obvious options:
1. move nodes around by moving the data (easy)
2. move nodes around by literally reorgansing the list through the pointers to nodes (harder) - NOT CURRENTLY IMPLEMENTED

*/

#include <iostream>
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
    
    //swap the data values - O(1)
    void swap(T &a, T &b) const // this is basically std::swap(a,b);
    {
        T temp = std::move(a);
        a = std::move(b);
        b = std::move(temp);
    }   

public:
    //ctors
    ListSort():List<T>(){}
    ListSort(std::vector<T> &data):List<T>(data){}

    template<typename func = decltype(lessThan<T>)>
    void bubbleSort(const func compare = lessThan<T>)
    {
        ptr *endPtr = nullptr; // start with end pointer being one past the end of the list
        ptr *startPtr = &this->root; //copy of root
        while (endPtr!=startPtr){ // if the end pointer is the start pointer we are done
            ptr *p = &this->root;    //start at root
            while (((*p)->next)&&(&(*p)->next!=endPtr)){
                if (((*p)->next) && ( compare( (*p)->next->data, (*p)->data ) )) //swap if out of order
                    swap((*p)->data, (*p)->next->data);
                p = &(*p)->next; //iterate
            }
            endPtr = p; //set the end point to the last value before loop exited, i.e. endPtr is prev to former endPtr
        }
    }
  
    //confirm sorted list - O(n)
    template<typename func = decltype(lessThan<T>)>
    bool checkSorted(const func compare = lessThan<T>)
    {
        ptr *p = &this->root;
        ptr *pNext = p;
        while ((*p)->next){
            pNext=&((*p)->next);
            if (compare((*pNext)->data, (*p)->data))
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
    
    uint32_t count=  0;

    while (1){
        std::cout<<std::endl<<std::endl<<"!!!!!!!!!!!NEW LIST!!!!!!!!!!!!!!!!!"<<std::endl<<std::endl;
        ListSort<T> listI{};
        for (size_t i=0;i<N;i++)
            listI.push_front(M*(2.0*rnd()-1.0));
        listI.bubbleSort();
        
        if (!listI.checkSorted()){   
            std::cout<<"not sorted! "<<count<<std::endl;
            listI.print();
            break;
        }
        else{
            listI.print();
            std::cout<<"sorted! "<<count<<std::endl;
        }

        ++count;
    }

    return 0;
}