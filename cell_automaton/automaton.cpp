#include "automaton.hpp"

#include <iomanip>
#include <iostream>
#include <random>

bool prob(double n) {
  std::random_device gen{};
  std::uniform_real_distribution<double> dis{0., 1.};
  return dis(gen) < n;
}

std::ostream& operator<<(std::ostream& os, Cell c) {
  if (c == Cell::S) {
    return os << "S";
  } else {
    return (c == Cell::I) ? os << "I" : os << "R";
  }
}

void Automaton::print() {
  for (int j = 0; j != height_; j++) {
    for (int i = 0; i != width_; i++) {
      std::cout << grid_[i + j * width_] << std::setw(4);
    }
    std::cout << '\n';
  }
}

Grid Automaton::state() { return grid_; }

bool Automaton::set(int i, Cell s) {
  if (grid_[i] != s) {
    grid_[i] = s;
    return true;
  }
  return false;
}

int Automaton::check(int const i, int const j, Grid g) {
  int n = 0;
  for (int k = i - 1; k != i + 2; k++) {
    for (int h = j - 1; h != j + 2; h++) {
      int tmp_k = k;
      int tmp_h = h;

      if (k < 0) {
        tmp_k += width_;
      }
      if (k >= width_) {
        tmp_k -= width_;
      }
      if (h < 0) {
        tmp_h += height_;
      }
      if (h >= height_) {
        tmp_h -= height_;
      }

      if (g[tmp_k + tmp_h * width_] == Cell::I) {
        n++;
      }
    }
  }
  return n;
}

void Automaton::evolve() {
  Grid yesterday = grid_;
  for (int i = 0; i != width_;
       i++) {  // i è l'indice di colonna, j quello di riga, l'indice del
               // vettore è [i + j * width]

    for (int j = 0; j != height_; j++) {
      if (yesterday[i + j * width_] == Cell::S) {
        int n = check(i, j, yesterday);
        if (prob(n * beta_ / 8)) {
          set(i + j * width_, Cell::I);
        }

      } else {
        if (yesterday[i + j * width_] == Cell::I) {
          if (prob(gamma_)) {
            set(i + j * width_, Cell::R);
          }
        }
      }
    }
  }
}
