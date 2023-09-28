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

Hash Table implementations

Two versions:

First:
Works through hashing with chaining
We hash the key to get an index
The index is for an element in an array where we store the key/value pairs
But intead we keep a linked list of key/value pairs there incase of a hash collision
We have a list for the O(1) removal if required

Second:
Works through linear probing
We hash the key to get an index in an array of key/value pairs
In case of collision we iterate from the index until we find the first free element

*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include "prime.hpp"

namespace structures_and_algorithms::structures::hashtables{

//HashTable class
template<typename T,typename U,typename func = std::hash<T> > //key, value, hash function
class HashTableChain{
protected:
    typedef std::pair<T,U> HashElement;
    const float MAX_LOAD = 0.5f; //arbitrary policy
    size_t primeIndex; //index in list of primes which determine number of buckets
    size_t N; //number of entries
    func hash; //hashing function
    std::vector<std::list<HashElement> > data; //where we keep the values
    float load; //load value - N / data.size()
    size_t get_bucket(const T& key)
    {
        return hash(key) % data.size(); //convert hash into a bucket index
    }
    bool rehash() // find the next size up (out of the primes) that leads to tolerable load then rehash
    {
        if (load > MAX_LOAD){ //some standard for too many collisions
            float proj_load = load;
            while (((proj_load > MAX_LOAD)&&(primeIndex < num_distinct_sizes_64_bit))){
                ++primeIndex;
                proj_load = static_cast<float>(N)/ static_cast<float>(g_a_sizes[primeIndex]);
            }
            rehash(g_a_sizes[primeIndex]);
            return true;
        }
        return false;
    }
    void rehash(const size_t& newSize) //resize and rehash the bucket array
    {
        std::list<HashElement> temp_list; //populate single list with all data
        for (auto &x: data)
            temp_list.splice(temp_list.end(), x);//moves x onto end of temp_list
        data.resize(newSize); //resize the array of buckets
        auto it = temp_list.begin(); //reinsert all the elements
        while (it != temp_list.end()){
            this->insert(std::move(*it));//load is updated in this call
            it = temp_list.erase(it); //moves the iterator to one past removed iterator
        }
    }
public:
    HashTableChain(func &hash_):primeIndex(0),N(0),hash(hash_),data(g_a_sizes[primeIndex],std::list<HashElement>()),load(0.0f)
    {}
    HashTableChain():primeIndex(0),N(0),hash(func()),data(g_a_sizes[primeIndex],std::list<HashElement>()),load(0.0f)
    {}

    U* find(const T& key) //return pointer to value associated with key if it is  in the table
    {
        std::list<HashElement> &l = data.at(get_bucket(key)); //get the list in the right bucket
        for (auto & x: l)
            if (x.first == key) //key type, T, must have "==" operator implemented 
                return &x.second;
        return nullptr; //returns nullptr if key not in the table
    }

    template<typename V> //takes universal/forwarding reference
    U& operator[] (V&& key) //return reference to value associated with key
    {
        std::list<HashElement> &l = data.at(get_bucket(key)); //get the list in the right bucket
        for (auto & x: l)
            if (x.first == key) //key type, T, must have "==" operator implemented 
                return x.second;
        l.emplace_back(HashElement(std::forward<V>(key),U()));
        ++N; //size increases by one
        load = static_cast<float> (N) / static_cast<float>(data.size()); //update load
        if (rehash())//resize as neccesary
            return (*this)[key]; //list changes if rehashed!
        else
            return l.back().second;
    }

    //perfect forward 'entry' using universal/forwarding reference
    template<typename V = std::pair<T,U> > //need default template type to deal with initialiser lists which have *no type*
    bool insert(V &&entry)
    {
        std::list<HashElement> &l = data.at(get_bucket(entry.first));
        for (const auto &x : l)
            if (x.first == entry.first) //key type, T, must have "==" operator implemented
                return false; //we fail to insert if the key already exists
        l.push_back(std::forward<V>(entry)); //insert the pair at the end of the list
        ++N; //size increases by one
        load = static_cast<float> (N) / static_cast<float>(data.size()); //update load
        rehash();//resize as neccesary
        return true;
    }

    bool remove(const T& key)
    {
        std::list<HashElement> &l = data.at(get_bucket(key));
        for (auto it = l.begin(); it != l.end(); ++it){
            if (it->first == key){
                l.erase(it); //erase the pair
                --N; //size decreases by one
                load = static_cast<float> (N) / static_cast<float>(data.size());//update load
                return true;
            }
        }
        return false;
    } 
    float getLoad()
    {
        return load;
    }
    size_t bucket_count()
    {
        return data.size();
    }
    size_t bucket(const T& key)
    {
        return get_bucket(key);
    }
    size_t bucket_size(const size_t& index)
    {
        return data.at(index).size();
    }
    void forceRehash()
    { //for testing purposes
        rehash(2*data.size());
    }
};

template<typename T,typename U,typename func = std::hash<T> > //key, value, hash function
class HashTableLinearProbe{
protected:
    typedef std::pair<T,U> HashElement;
    const float MAX_LOAD = 0.5f; //arbitrary policy
    size_t primeIndex; //index in list of primes which determine number of buckets
    size_t N; //number of entries
    func hash; //hashing function
    std::vector<std::unique_ptr<HashElement> > data; //where we keep the values
    float load; //load value - N / data.size()
    size_t get_bucket(const T& key)
    {
        return hash(key) % data.size(); //convert hash into a bucket index
    }
    bool rehash() // find the next size up (out of the primes) that leads to tolerable load then rehash
    {
        if (load > MAX_LOAD){ //some standard for too many collisions
            float proj_load = load;
            while (((proj_load > MAX_LOAD)&&(primeIndex < num_distinct_sizes_64_bit))){
                ++primeIndex;
                proj_load = static_cast<float>(N)/ static_cast<float>(g_a_sizes[primeIndex]);
            }
            rehash(g_a_sizes[primeIndex]);
            return true;
        }
        return false;
    }
    void rehash(const size_t& newSize) //resize and rehash the bucket array
    {
        std::vector<std::unique_ptr<HashElement> > temp_data; //populate single list with all data -auto freed at eos
        for (auto &x : data)
            if (x)
                temp_data.emplace_back(std::move(x));
        data.resize(newSize); //resize the array of buckets
        for (auto &x : temp_data)
            this->insert(std::move(*x));  
    }
public:
    HashTableLinearProbe(func &hash_):primeIndex(0),N(0),hash(hash_),data(g_a_sizes[primeIndex]),load(0.0f)
    {}
    HashTableLinearProbe():primeIndex(0),N(0),hash(func()),data(g_a_sizes[primeIndex]),load(0.0f)
    {}

    U* find(const T& key) //return pointer to value associated with key if it is  in the table
    {
        size_t index = get_bucket(key);
        std::unique_ptr<HashElement> *ptr = &data.at(index);
        U* ret = nullptr;
        while (*ptr){
            if ((*ptr)->first == key)
                ret = &(*ptr)->second;
            ptr = &data.at(++index % data.size());
        }
        return ret;
    }

    template<typename V>
    U& operator[] (V&& key) //return reference to value associated with key
    {
        size_t index = get_bucket(key); //get the right bucket
        std::unique_ptr<HashElement> *ptr = &data.at(index);
        while (*ptr){
            if ((*ptr)->first == key)
                return (*ptr)->second;
            ptr = &data.at(++index % data.size());
        }
        *ptr = std::make_unique<HashElement>(HashElement(std::forward<V>(key),U())); 
        ++N; //size increases by one
        load = static_cast<float> (N) / static_cast<float>(data.size()); //update load
        if (rehash())//resize as neccesary
            return (*this)[key]; //ptr changes if rehashed!
        else
            return (*ptr)->second;        
    }

    template<typename V = std::pair<T,U> > //need default template type to deal with initialiser lists which have *no type*
    bool insert(V &&entry)
    {
        size_t index = get_bucket(entry.first);
        std::unique_ptr<HashElement> *ptr = &data.at(index);
        while (*ptr){
            if ((*ptr)->first == entry.first)
                return false;
            ptr = &data.at(++index % data.size());
        }
        *ptr = std::make_unique<HashElement>(std::forward<V>(entry));   
        ++N; //size increases by one
        load = static_cast<float> (N) / static_cast<float>(data.size()); //update load
        rehash();//resize as neccesary
        return true;
    }

    bool remove(const T& key)
    {
        size_t index = get_bucket(key);
        std::unique_ptr<HashElement> *ptr = &data.at(index);
        while (*ptr){
            if ((*ptr)->first == key)
            {
                (*ptr).reset();
                return true;
            }
            ptr = &data.at(++index % data.size());
        }
        return false;
    } 
    float getLoad()
    {
        return load;
    }
    size_t bucket_count()
    {
        return data.size();
    }
    size_t bucket(const T& key)
    {
        return get_bucket(key);
    }
    void forceRehash()
    { //for testing purposes
        rehash(2*data.size());
    }
};

}

#endif /*HASHTABLE_H*/
