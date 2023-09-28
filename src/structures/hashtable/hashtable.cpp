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

Hash Table

*/

#include <iostream>
#include <string>
#include "hashtable.hpp"

using namespace structures_and_algorithms::structures::hashtables;

//example hash functor for an int for method 2.
struct IntHash { 
    size_t operator()(const int& i) const
    {
        return std::abs(i);
    }
};

template<template<typename,typename,typename> typename h,typename T, typename U,typename f>
void test(h<T,U,f> & ht){
    for (auto key : {23,43,25,27,47,137,98}){
        if (ht.find(key)) //nullptr if not found
            std::cout<<*ht.find(key)<<std::endl;
        else
            std::cout<<"element with key "<<key<<" not found"<<std::endl;
    }
}

int main(/*int argc, char* argv[]*/)
{   
    typedef int32_t T;
    typedef std::string U;
    
    //all the below should work:
    #define DECL 3
    #if DECL == 1
    std::cout<<"Using lambda hash"<<std::endl;
    constexpr auto hashfn = [](const T& key)->size_t{return std::abs(key);};//example hash function
    HashTableLinearProbe<T,U,decltype(hashfn)> ht(hashfn);// = HashTableChain<T,U,decltype(hash)>(hash);
    #elif DECL == 2
    std::cout<<"Using functor hash"<<std::endl;
    HashTableLinearProbe<T,U,IntHash> ht;
    #else
    std::cout<<"Using default hash"<<std::endl;
    typedef HashTableChain<T,U> HashTable;
    HashTable ht;
    #endif

    //insert in different ways
    std::pair<T,U> p1 = {23,"boat"};
    ht.insert(p1);
    std::pair<T,U> p2 = {43,"truck"};
    ht.insert(std::move(p2));
    ht.insert(std::pair<int32_t,std::string>(25,"moped"));
    std::string str1 = "plane";
    ht.insert(std::pair<int32_t,std::string>(27,str1));
    ht[47]="car";
    std::string str2 = "ship";
    ht[137]=str2;
    ht.insert({98,"helicopter"});
    
    //test the container
    test(ht);
    //remove an element
    int32_t removedKey = 25;
    ht.remove(removedKey);
    std::cout<<std::endl<<"removed key "<<removedKey<<std::endl;
    //test the container
    test(ht);
    //rehash the contents
    ht.forceRehash();
    std::cout<<std::endl<<"rehashed"<<std::endl;
    //test the container
    test(ht);
    return 0;  
}