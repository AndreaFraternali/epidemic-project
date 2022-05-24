//serve solo per la fase di test, poi va tolto


#include <iomanip>
#include <iostream>

#include "epidemic.hpp"

// dobbiamo mettere parametri selezionabili dall'utente
int main() {
  double gamma;  // non so se ci va il _ :-)
  double beta;
  double v_ratio;
  int S;
  int I;
  int R;
  int days;
  //andre so che non apprezzerai questa parte
  std::cout<< "gamma " ; std::cin >> gamma;
  std::cout<< "beta "; std::cin >> beta;
  std::cout<< "S "; std::cin >> S;
  std::cout<< "I "; std::cin >> I;
  std::cout<< "R "; std::cin >> R;
  std::cout<< "days "; std::cin >> days;
  Day today{S, I, R};
  Epidemic epidemic{gamma, beta, today};
  epidemic.evolve(days);
  std::cout << epidemic.state() << '\n';
}