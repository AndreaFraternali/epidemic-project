#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP

#include <random>
#include <vector>

enum class Cell { S, I, R };

class Grid {
  std::vector<Cell> grid_;
  int width_;
  int heigth_;

 public:
  Grid(int width, int heigth) : width_{width}, heigth_{heigth} {

    for(int i = 0; i != heigth * width; i++){
      grid_.push_back(Cell::S);
    }

  };

  std::vector<Cell> state();

  void evolve(int d);
};

#endif