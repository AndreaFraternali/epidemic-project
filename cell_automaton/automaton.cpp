
// uso random per mettere un suscettibile in un punto a caso (se si può fare)
// uso random per confrontarlo con probabilità gamma di infettarsi
// usiamo n/8 * beta probabilità di infettarsi con n numero di infetti intorno
// se volessimo fare un test, solo griglia con evolve(0) che restituisce se
// stessa
#include "automaton.hpp"
#include <random>

bool prob(double n) {
  std::random_device gen{};
  std::uniform_real_distribution<double> dis{0., 1.};
  return dis(gen) < n;
}

std::vector<Cell> Grid::state() { return grid_; }

int Grid::check(int const i, int const j) {
  int n = 0;
  for (int k = i - 1; k != i + 2; k++) {

    for (int h = j - 1; h != j - 2; h++) {

      if (grid_[k + h * width_] == Cell::I) {
        n++;
      }

    }

  }
  return n;
}

void Grid::evolve(int d) {
  for (int i = 0; i < width_;
       i++) {  // i è l'indice di colonna, j quello di riga, l'indice del
               // vettore è [i + j * width]
    
    for (int j = 0; j < heigth_; j++) {

      if (grid_[i + j * width_] == Cell::S) {

        int n = check(i, j);
        if (prob(n * beta_ / 8)) {
          grid_[i + j * width_] = Cell::I;
        }

      } else {

        if (grid_[i + j * width_] == Cell::I) {
          
          if (prob(gamma_)) {
            grid_[i + j * width_] = Cell::R;
          }

        }
      }
    }
  }
}
