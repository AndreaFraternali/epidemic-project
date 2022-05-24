#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP

#include <vector>

enum class Cell { S, I, R };

class Grid {
  std::vector<Cell> grid_;
  int width_;
  int heigth_;
  double beta_; // prob da S a I quando delle celle S attorno ad I
  double gamma_; // prob da I a R in generale

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