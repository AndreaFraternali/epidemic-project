#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP

#include <ostream>
#include <vector>
#include <random>

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
  explicit Automaton(int width, int height, double beta, double gamma,
                     int init_inf, int init_rem)
      : width_{width}, height_{height}, beta_{beta}, gamma_{gamma} {
    // handling exceptions
    if (width <= 0 || height <= 0) {
      throw std::runtime_error(
          "Le dimensioni della griglia devono essere strettamente positive");
    }
    if (gamma < 0 || gamma > 1) {
      throw std::runtime_error(
          "Il parametro gamma deve essere compreso tra 0 e 1");
    }
    if (beta < 0 || beta > 1) {
      throw std::runtime_error(
          "Il parametro beta deve essere compreso tra 0 e 1");
    }
    if (init_inf > width * height) {
      throw std::runtime_error(
          "Il numero di infetti iniziali supera il totale della popolazione");
    }
    if (init_rem > width * height) {
      throw std::runtime_error(
          "Il numero di rimossi iniziali supera il totale della popolazione");
    }
    if (init_inf + init_rem > width * height) {
      throw std::runtime_error(
          "Il numero di infetti e rimossi iniziali supera il totale della "
          "popolazione");
    }
    if (init_inf <= 0) {
      throw std::runtime_error(
          "L'automa cellulare non si evolve con questi dati iniziali");
    }
    // setting all the cells to S
    for (int i = 0; i != height_ * width_; i++) {
      grid_.push_back(Cell::S);
    }
    // setting init_inf and init_rem
    std::random_device gen{};
    std::uniform_int_distribution<int> dis{0, width * height - 1};
    for (int i = 0; i != init_inf;) {
      int n = dis(gen);
      if (set(n, Cell::I)) {
        i++;
      }
    }
    for (int i = 0; i != init_rem;) {
      int n = dis(gen);
      if (set(n, Cell::R)) {
        i++;
      }
    }
  };

  explicit Automaton() = default;

 private:
  int check(int const i, int const j,
            Grid grid);  // checks number of infected people in 8 cells around
                         // [i + j * 4]-th one

 public:
  bool set(int i,
           Cell s);  // returns true if [i]-th cell is not s at present
  Grid state();
  void evolve();
};

#endif