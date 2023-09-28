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

Insertion sort

Average performance O(n^2)

1. Loop over list
2. With each value move it to the correct place in the array in front of it
3. This necessitates "shifting" the whole array between its original position and new position "up one" place

We do this by looping
i: 1 -> n-1
store value to be inserted val = data[i]
Then loop j: i-1 -> 0
while looking at bigger values than "val" move every element up one: data[j+1]=data[j]
Then insert the value in the place where you end up
data[j+1] = val
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
public:
    typedef typename List<T>::Node Node; // dependent names (depends on T) are not interpreted as types by default - must add typename
                                         // also need scope resolution
    ListSort():List<T>(){}
    ListSort(const std::vector<T> &data):List<T>(data){}
    template<typename func = decltype(lessThan<T>)>
    void insertionSort(const func compare = lessThan<T>){

        ListSort<T> sorted; // new list to be built

        Node *ptr = this->root.get(); //iterate over list to be sorted
        while (ptr){ //ptr is node to be inserted
            Node *p = sorted.getRoot().get(); // start at beginning of sorted list (starts empty)
            int32_t j=0; //keep track of index of sorted list
            T val = ptr->data; //value of data/node to be inserted
            while ((p)&&(compare(p->data, val))){ //keep moving through sorted list until empty or we find a bigger value
                p = p->next.get();
                j++;
            }
            //at this point j is the index in the sorted list where val needs to go
            sorted.insert(j,val); // insert val
            this->remove(0); //remove the node that was inserted into sorted from the original list
            ptr = this->root.get(); //take the next node in the list which is now in the root position
        }
        this->root = std::move(sorted.getRootVol()); //move the sorted list into the place of the data
    }
};


int main(/*int argc, char* argv[]*/)
{
    typedef double T;
    const size_t N=10;
    const T M=100;
    RndUniform rnd;
    ListSort<T> list{};
    for (size_t i=0;i<N;i++)
        list.push_front(M*(2.0*rnd()-1.0));

    std::cout<<"before sort"<<std::endl<<std::endl;
    list.print();
    list.insertionSort();
    std::cout<<std::endl<<"after sort"<<std::endl<<std::endl;
    list.print();

    return 0;
}