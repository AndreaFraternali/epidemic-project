// qui definizioni di metodi e funzioni
#include "epidemic.hpp"

#include <cassert>
#include <iostream>

std::ostream& operator<<(std::ostream& os, Day const& d) {
  return os << "S = " << (int)d.S << ", I = " << (int)d.I << ", R = " << (int)d.R;
}

Day Epidemic::state() { return today_; }

double Epidemic::getBeta() { return beta_; }

double Epidemic::getGamma() { return gamma_; }

void Epidemic::evolve(int d) {
  double const N = today_.S + today_.R + today_.I;
  assert(N > 0);

  for (int i = 0; i != d; ++i) {
    auto yesterday = today_;
    today_.S = yesterday.S - beta_ * (yesterday.S / N) * yesterday.I;
    today_.I = yesterday.I + beta_ * (yesterday.S / N) * yesterday.I -
               gamma_ * yesterday.I;
    today_.R = yesterday.R + gamma_ * yesterday.I;
    //assert(today_.S + today_.I + today_.R < N + 1 &&
          // today_.S + today_.I + today_.R > N - 1);
  }
}
