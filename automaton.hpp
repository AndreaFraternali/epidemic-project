#ifndef AUTOMATON_HPP
#define AUTOMA_HPP


#include <vector>
#include<random>

  enum class Cell {S, I, R};

class Grid{
    int side_;
    std::vector<Cell> row;
    std::vector<std::vector<Cell>> column; //perchè non posso fare vettore di righe?
    
    public: Grid(int side): side_(side)  {};
     
    for(int i=0, i<side, ++i) { //???
    row.push_back(Cell::S);
    }
    
     

};

#endif