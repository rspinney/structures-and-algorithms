/*****************************************************************************/
/***************** Copyright (C) 2020-2021, Richard Spinney. *****************/
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

#ifndef RANDOM_H
#define RANDOM_H

#include <math.h>
#include <random>
#include <cmath>
#include <algorithm>
#include <ctime>

// class wrapper for c++11 uniform distribution of psuedo-random numbers
// using templates for different generators, e.g. Mersenne Twister algo.

// possible types for template argument:
// std::minstd_rand
// std::mt19937
// std::mt19937_64

namespace structures_and_algorithms::random{

template<typename T = std::mt19937> //default type - >= c++17 only
class RndBase{
private:
	void init_seed(){
		std::array<int32_t,624> seedData;//fill the MT registers with random numbers
		std::random_device rndDev;
		std::generate_n(seedData.data(),seedData.size(),std::ref(rndDev));
		std::seed_seq seq(std::begin(seedData),std::end(seedData));
		m_eng = T(seq);
	}
protected:
	T m_eng;
public:
	RndBase(){init_seed();}
	RndBase(const int32_t a_seed):m_eng(a_seed){};
};

template<typename T = std::mt19937>
class RndUniform : public RndBase<T>{
private:
	std::uniform_real_distribution<double> m_dist;
public:
	double operator() (){return m_dist(RndBase<T>::m_eng);}
	RndUniform(const double a_lowerBound,const double a_upperBound,const int32_t a_seed):RndBase<T>(a_seed),m_dist(a_lowerBound,a_upperBound){}
	RndUniform(const double a_lowerBound,const double a_upperBound):RndBase<T>(),m_dist(a_lowerBound,a_upperBound){}
	RndUniform(const int32_t a_seed):RndBase<T>(a_seed),m_dist(0.0,1.0){}
	RndUniform():RndBase<T>(),m_dist(0.0,1.0){}
	
};

template<typename T = std::mt19937>
class RndBinom : public RndBase<T>{
private:
	std::binomial_distribution<uint64_t> m_dist;
	int32_t m_n;
public:
	double operator() (){return static_cast<double>(m_dist(RndBase<T>::m_eng))/static_cast<double>(m_n);}
	RndBinom(const int32_t a_n,const double a_p,const int32_t a_seed):RndBase<T>(a_seed),m_dist(a_n,a_p),m_n(a_n){}
	RndBinom(const int32_t a_n,const double a_p):RndBase<T>(),m_dist(a_n,a_p),m_n(a_n){}
};

template<typename T = std::mt19937>
class RndGauss : public RndBase<T>{
private:
	std::normal_distribution<double> m_dist;
public:
	double operator() (){return m_dist(RndBase<T>::m_eng);}
	double operator () (double a_mu,double a_sigma){
		m_dist = std::normal_distribution<double>(a_mu,a_sigma);
		return m_dist(RndBase<T>::m_eng);
	} 
	RndGauss(const double a_mu,const double a_sigma,const int32_t a_seed):RndBase<T>(a_seed),m_dist(a_mu,a_sigma){}
	RndGauss(const double a_mu,const double a_sigma):RndBase<T>(),m_dist(a_mu,a_sigma){}
	RndGauss(const int32_t a_seed):RndBase<T>(a_seed),m_dist(0.0,1.0){}
	RndGauss():RndBase<T>(),m_dist(0.0,1.0){}
};

}

#endif /*RANDOM_H*/
