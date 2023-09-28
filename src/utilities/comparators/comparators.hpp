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

Simple comparator lambdas

*/

#ifndef COMPARATOR_H
#define COMPARATOR_H

namespace structures_and_algorithms::comparators{

template<typename T>
constexpr auto lessThan = [](const T &a,const T &b)->bool{return a < b;};
template<typename T>
constexpr auto greaterThan = [](const T &a,const T &b)->bool{return a > b;};

}

#endif /*COMPARATOR_H*/