#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP

#include <algorithm>
#include <random>
#include <stdexcept>
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
  explicit Automaton(int width, int height, double beta, double gamma,
                     int init_inf, int init_rem)
      : grid_(width * height, Cell::S), width_{width}, height_{height}, beta_{beta}, gamma_{gamma} {
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

    // setting init_inf and init_rem
   auto it = std::fill_n(grid_.begin(), init_inf, Cell::I);
    std::fill_n(it, init_rem, Cell::R);
    std::random_device gen{};
    std::default_random_engine g{gen()};
    std::shuffle(grid_.begin(), grid_.end(), g);
  }

  explicit Automaton() = default;

 private:
  int check(int const i, int const j,
            Grid const& grid) const;  // checks number of infected people in 8
                                     // cells around [i + j * width]-th one

 public:
  bool set(int const i,
           Cell const s);  // returns true if [i]-th cell is not s at present
  Grid const& state() const;
  void evolve();
};

#endif