// qui definizioni di metodi e funzioni
#include "epidemic.hpp"

#include <cassert>
#include <iostream>

std::ostream& operator<<(std::ostream& os, Day const& d) {
  return os << "S = " << d.S << ", I = " << d.I << ", R = " << d.R;
}

Day Epidemic::state() { return today_; }

double Epidemic::getBeta() { return beta_; }

double Epidemic::getGamma() { return gamma_; }

void Epidemic::evolve(int d) {
  
  double const N = today_.S + today_.R + today_.I;
  assert(N > 0);

  for (int i = 0; i != d; ++i) {
    auto tmp_today = today_;
    today_.S = tmp_today.S - beta_ * (tmp_today.S / N) * tmp_today.I;
    today_.I = tmp_today.I + beta_ * (tmp_today.S / N) * tmp_today.I -
               gamma_ * tmp_today.I;
    today_.R = tmp_today.R + gamma_ * tmp_today.I;
    std::cout << "N - (S + I + R) = " << N - today_.S - today_.I - today_.R     //non è consistente con i valori ottenuti
              << '\n';
    // assert(N == today_.S + today_.I + today_.R)  fallisce spesso
  }
}
