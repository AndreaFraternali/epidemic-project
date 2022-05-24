
// uso random per mettere un suscettibile in un punto a caso (se si può fare)
// uso random per confrontarlo con probabilità gamma di infettarsi
// usiamo n/8 * beta probabilità di infettarsi con n numero di infetti intorno
// se volessimo fare un test, solo griglia con evolve(0) che restituisce se
// stessa
#include "automaton.hpp"
#include <random>

std::vector<Cell> Grid::state() { return grid_; }

void Grid::evolve(int d) {
  for (int i = 0; i < width_;
       i++) {  // i è l'indice di colonna, j quello di riga, l'indice del
               // vettore è [i + j * width]
    for (int j = 0; j < heigth_; j++) {
      if (grid_[i + j * width_] == Cell::S) {

      } else {
        if (grid_[i + j * width_] == Cell::I) {
            
        }
      }
    }
  }
}
