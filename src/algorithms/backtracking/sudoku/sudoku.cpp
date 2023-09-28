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

Sudoku solver via backtracking

*/

#include <iostream>
#include <iomanip>
#include <array>
#include <string>

template<size_t N = 3>
class Sudoku{
    bool error = false;
    std::array<std::array<size_t,N*N>,N*N > table;

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
    Sudoku()// will construct an (arbitrary, but not random) completed sudoku.
    {
        std::cout<<"Generating Sudoku of size: "<< N * N <<std::endl<<std::endl;
        for (auto &x:table)
            x.fill(0);
    } 
    template<typename T>
    Sudoku(const std::array<std::array<T,N*N>,N*N > &input)
        :table(input)
    {
        static_assert(std::is_integral<T>::value, "Integral type required.");
        static_assert(std::is_unsigned<T>::value, "Unsigned type required.");
        std::cout<<"Input:"<<std::endl;
            print();
    }

    void solve()
    {
        bool solved = recursiveSolve();
        if (solved){
            std::cout<<"Solved:"<<std::endl;
            print();
            std::cout<<std::endl;
        }
        else{
            std::cout<<"No Solution!"<<std::endl;
        }
    }

    std::array<std::array<size_t,N*N>,N*N > get()
    {
        return table;
    }
};




int main(/*int argc, char* argv[]*/)
{
    typedef std::array<std::array<size_t,9>,9 > T;
    T input = 
    {{
        {3, 0, 6, 5, 0, 8, 4, 0, 0}, 
        {5, 2, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 8, 7, 0, 0, 0, 0, 3, 1}, 
        {0, 0, 3, 0, 1, 0, 0, 8, 0}, 
        {9, 0, 0, 8, 6, 3, 0, 0, 5}, 
        {0, 5, 0, 0, 9, 0, 6, 0, 0}, 
        {1, 3, 0, 0, 0, 0, 2, 5, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 7, 4}, 
        {0, 0, 5, 2, 0, 6, 3, 0, 0} 
    }};

    Sudoku s3(input);
    s3.solve();

    Sudoku<4> s4;
    s4.solve();
    
    return 0;
}
