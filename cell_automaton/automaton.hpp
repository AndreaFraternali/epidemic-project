#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP

#include <ostream>
#include <vector>

enum class Cell { S, I, R };

std::ostream& operator<<(std::ostream& os, Cell c);

using Grid = std::vector<Cell>;
class Automaton {
  Grid grid_;
  int width_;
  int heigth_;
  double beta_;   // prob da S a I quando delle celle S attorno ad I
  double gamma_;  // prob da I a R in generale

 public:
  Automaton(int width, int heigth, double beta, double gamma)
      : width_{width}, heigth_{heigth}, beta_{beta}, gamma_{gamma} {
    for (int i = 0; i != heigth_ * width_; i++) {
      grid_.push_back(Cell::S);
    }
  };

  int check(int const i, int const j,
            Grid grid);  // controlla quanti infetti ci sono nelle 8 celle
                         // intorno alle (i + j * 4)-esima
  void evolve();

  bool set(int i, Cell s);  // restituisce true se attualmente la cella i è diversa da s

  void print();
};

#endif