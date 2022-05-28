#include "automaton.hpp"

#include <iostream>
#include <random>

int main() {
  int const width = 4;
  int const heigth = 4;
  double beta = 0.1;
  double gamma = 0.2;
  Automaton autom{width, heigth, beta, gamma};
  int const init_inf = width * heigth / 4;
  std::random_device gen{};
  std::uniform_int_distribution<int> dis{0, width * heigth - 1};
  int i = 0;
  do {
    int n = dis(gen);
    if (autom.set(n, Cell::I)) {
      i++;
    }
  } while (i != init_inf);
  int const days = 3;
  autom.print();
  for (int i = 0; i != days; i++) {
    std::cout << '\n' << '\n';
    autom.evolve();
    autom.print();
  }
}
