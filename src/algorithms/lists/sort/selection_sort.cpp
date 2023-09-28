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

Selection sort

Average performance O(n^2) - not an efficient sorting algorithm for real use

1. Loop over array of length n with index i
2. In sub-array [i,n] find smallest/largest element and move to index i
3. i <- i + 1

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
    void selectionSort(const func compare = lessThan<T>)
    {
        ptr *p = &this->root;
        bool inRange = true;
        while (inRange){
            ptr *q = p;
            ptr *min = p;
            bool inRangeInner = true;
            while (inRangeInner){
                if (compare((*q)->data,(*min)->data))
                    min = q; //found min
                if ((*q)->next)
                    q = &(*q)->next; //iterate
                else
                    inRangeInner = false; // exit
            }
            swap((*p)->data,(*min)->data);
            if ((*p)->next)
                p = &(*p)->next; //iterate
            else
                inRange = false; //exit
        }
    }
  
    //confirm sorted list - O(n)
    template<typename func = decltype(lessThan<T>)>
    bool checkSorted(const func compare = lessThan<T>)
    {
        ptr *p = &this->root;
        ptr *pNext = p;
        while (*p){
            pNext=&((*p)->next);
            if ((*pNext)&&(compare((*pNext)->data, (*p)->data)))
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

    while (count < 100){
        std::cout<<std::endl<<std::endl<<"!!!!!!!!!!!NEW LIST!!!!!!!!!!!!"<<std::endl<<std::endl;
        ListSort<T> listI{};
        for (size_t i=0;i<N;i++)
            listI.push_front(M*(2.0*rnd()-1.0));
        listI.print();
        listI.selectionSort(greaterThan<T>);
        
        if (!listI.checkSorted(greaterThan<T>)){   
            std::cout<<"not sorted! "<<count<<std::endl;
            listI.print();
            break;
        }
        else{
            std::cout<<std::endl<<"sorted! count: "<<count<<std::endl<<std::endl;
            listI.print();
        }

        ++count;
    }

    return 0;
}