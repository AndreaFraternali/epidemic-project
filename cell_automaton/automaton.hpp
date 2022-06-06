#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP

#include <ostream>
#include <vector>

enum class Cell { S, I, R };

bool prob(double n);

using Grid = std::vector<Cell>;
class Automaton {
  Grid grid_;
  int width_;
  int height_;
  double beta_;   
  double gamma_;  

 public:
  explicit Automaton(int width, int height, double beta, double gamma)
      : width_{width}, height_{height}, beta_{beta}, gamma_{gamma} {
    for (int i = 0; i != height_ * width_; i++) {
      grid_.push_back(Cell::S);
    }
    if(width <= 0 || height <= 0){
      throw std::runtime_error("Le dimensioni della griglia devono essere strettamente positive");
    }
    if(gamma < 0 || gamma > 1){
      throw std::runtime_error("Il parametro gamma deve essere compreso tra 0 e 1");
    }

    if(beta < 0 || beta > 1){
      throw std::runtime_error("Il parametro beta deve essere compreso tra 0 e 1");
    }
  };

  explicit Automaton() = default;

 private:
  int check(int const i, int const j,
            Grid grid);  //check numbers of infected people in 8 cells around [i + j * 4]-th one

 public:
  bool set(
      int i,
      Cell s);  // returns true if [i]-th cell is not s at present
  Grid state();
  void evolve();
};

#endif