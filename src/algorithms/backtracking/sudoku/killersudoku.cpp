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

Killer Sudoku solver via backtracking

*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <string>
#include <unordered_map>

template<size_t N = 3>
class KillerSudoku{
    constexpr static size_t N2 = N * N;
    bool error = false;
    std::array<std::array<size_t,N*N>,N*N > table;
    std::array<std::array<size_t,N*N>,N*N > boxes;
    std::vector<size_t> boxSums;
    struct hasher{ //hash functor for pair
        size_t operator()(const std::pair<size_t,size_t> &val)const{ return N*N*val.first + val.second;}
    };
    std::unordered_map<std::pair<size_t,size_t>,size_t,hasher> boxMembership;
    std::vector<std::vector<std::pair<size_t,size_t> > > boxLists;

    void printSimple() const
    {
        for (auto const &x:table){
            for (auto const &xx:x)
                std::cout<<xx<<" ";
            std::cout<<std::endl;
        }
    }

    void print() const
    {
        for (size_t i=0;i<3*N*N+1;++i)
            std::cout<<"-";
        std::cout<<std::endl;
        for (size_t i=0;i<N;++i){
            for (size_t ii = 0;ii<N;++ii){
                size_t row = i*N + ii;
                std::cout<<"|";
                for (size_t j = 0;j<N;++j){
                    for (size_t jj = 0;jj<N;++jj){
                        size_t column = j*N+jj;
                        if (jj<N-1)
                            std::cout<<std::setw(2)<<table[row][column]<<" ";
                        else
                            std::cout<<std::setw(2)<<table[row][column];
                    }
                    std::cout<<"|";
                }
                std::cout<<std::endl;
            }
            
            if (i<N-1) std::cout<<"|";
            else std::cout<<"--";
            for (size_t k=0;k<3*N*N-1;++k)
                std::cout<<"-";
            if (i<N-1)std::cout<<"|";
            std::cout<<std::endl;
        }
    }

    bool getFreeElement(size_t &row,size_t &column) const
    {
        for (size_t i=0;i<N*N;++i){
            for (size_t j=0;j<N*N;++j){
                if (table[i][j]==0){
                    row = i;
                    column = j;
                    return true;
                }
            }
        }
        return false;
    }
    
    bool check(size_t val,size_t row,size_t column) const
    {
        //usual sudoku constraints
        for (size_t i = 0; i<N*N;++i){
            if (table[row][i]==val) return false;
            if (table[i][column]==val) return false;
        }
        size_t ri = row/N;
        size_t ci = column/N;
        for (size_t i = ri*N; i < (ri+1)*N;++i)
            for (size_t j = ci*N; j < (ci +1)* N;++j)
                if (table[i][j]==val)
                    return false;

        //box constraints
        //find box
        const size_t boxIndex = boxMembership.at({row,column});
        //list of elements in box
        const std::vector<std::pair<size_t,size_t> > &box = boxLists[boxIndex];
        //target sum of box
        size_t boxSum = boxSums[boxIndex];
        size_t sum = 0; //count total in box
        size_t used = 0; //count number of used elements in box

        for (size_t i=0;i<box.size();++i){
            const size_t ir = box[i].first; //row of element of box
            const size_t ic = box[i].second;//column of element of box
            if (table[ir][ic] == val) // if value is already in box
                return false;
            sum += table[ir][ic];
            if (sum + val > boxSum) //if adding value exceed box sum
                return false;
            if (table[ir][ic] !=0) //count how many elements of box are filled
                ++used;
        }

        if (used == box.size()-1)//last element must make the total exactly
            if (sum+val!=boxSum)
                return false;
    
        return true;
    }

    bool recursiveSolve()
    {
        //print();
        size_t row,column;
        bool found = getFreeElement(row,column);
        if (!found)
            return true; // solved!
        for (size_t val = 1; val <= N*N; ++val){
            if (check(val,row,column)){
                table[row][column] = val;
                if (recursiveSolve()){
                    return true;
                }
                table[row][column] = 0; //undo mistakes
            }
        }
        return false;
    }

public:
    template<typename T,typename U>
    KillerSudoku(const std::array<std::array<T,N*N>,N*N > &inputBoxes,const std::vector<U> &values)
        :boxes(inputBoxes),boxSums(values)
    {
        static_assert(std::is_integral<T>::value, "Integral type required.");
        static_assert(std::is_unsigned<T>::value, "Unsigned type required.");
        static_assert(std::is_integral<U>::value, "Integral type required.");
        static_assert(std::is_unsigned<U>::value, "Unsigned type required.");

        for (auto &x:table)
            x.fill(0);

        boxLists = std::vector<std::vector<std::pair<size_t,size_t>> >(values.size());

        for (size_t i = 0;i<N*N;++i){
            for (size_t j = 0;j<N*N;++j){
                boxMembership[{i,j}] = boxes[i][j]-1;
                boxLists[boxes[i][j]-1].push_back({i,j});
            }
        }

        std::cout<<"Input:"<<std::endl;
        print();
        
    }

    void solve()
    {
        if (error){
            std::cout<<"There is a problem with this input."<<std::endl;
            return;
        }
        bool solved = recursiveSolve();
        if (solved){
            std::cout<<"Solved:"<<std::endl;
            print();
        }
        else{
            std::cout<<"No Solution!"<<std::endl;
        }
    }

    std::vector<std::vector<size_t> > get()
    {
        return table;
    }
};

int main(/*int argc, char* argv[]*/)
{
    typedef std::array<std::array<size_t,9>,9 > T;
    T grid = 
    {{
        {  1,  2,  2,  3,  4,  5,  5,  6,  6}, 
        {  1,  7,  7,  3,  4,  8,  9,  6, 10}, 
        { 11, 12,  7, 13, 14,  8,  9,  9, 10}, 
        { 11, 12,  7, 13, 14, 15, 15, 16, 17}, 
        { 18, 18, 18, 18, 14, 19, 16, 16, 17}, 
        { 20, 21, 18, 22, 22, 19, 23, 24, 25}, 
        { 20, 21, 26, 27, 27, 19, 23, 24, 25}, 
        { 20, 21, 26, 28, 29, 29, 23, 24, 30}, 
        { 20, 20, 28, 28, 31, 32, 32, 30, 30} 
    }};
    std::vector<size_t> values = 
    { 
        9,    //1
        9,    //2
        5,     //3
        17,     //4
        13,     //5
        18,     //6
        15,     //7
        11,     //8
        12,     //9
        8,    //10
        9,     //11
        12,    //12
        7,    //13
        15,    //14
        11,    //15
        15,    //16
        11,    //17
        34,     //18
        15,     //19
        28,     //20
        16,     //21
        9,      //22
        13,     //23
        10,     //24
        11,     //25
        7,      //26
        5,      //27
        20,     //28
        9,      //29
        16,     //30
        2,      //31
        13      //32
    };

    //Sudoku s(input);
    KillerSudoku<3> s(grid,values);
    s.solve();
    
    return 0;
}
