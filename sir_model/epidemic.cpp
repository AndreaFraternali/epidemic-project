#include "epidemic.hpp"

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>

std::ostream& operator<<(std::ostream& os, Day const& d) {
  return os << std::setw(8) << "S = " << d.S << std::setw(8) << "I = " << d.I << std::setw(8) << "R = " << d.R;
}

bool operator==(Day const& d1, Day const& d2){
  return d1.S == d2.S && d1.I == d2.I && d1.R == d2.R;
}

double fractional(double x) { return x - std::floor(x); }

Day Epidemic::state() { return today_; }

double Epidemic::getBeta() { return beta_; }

double Epidemic::getGamma() { return gamma_; }

void Epidemic::evolve(int d) {
  
  double const N = today_.S + today_.R + today_.I;
  assert(N > 0);

  for (int i = 0; i != d; ++i) {
    auto yesterday = today_;

    double tmp_S = yesterday.S - beta_ * (yesterday.S / N) * yesterday.I - v_ratio_ * yesterday.S;
    double tmp_I = yesterday.I + beta_ * (yesterday.S / N) * yesterday.I -
                   gamma_ * yesterday.I;
    double tmp_R = yesterday.R + gamma_ * yesterday.I + v_ratio_ * yesterday.S;

    today_.S = std::round(tmp_S);
    today_.I = std::round(tmp_I);
    today_.R = std::round(tmp_R);

    double fract_S = fractional(tmp_S);
    double fract_I = fractional(tmp_I);
    double fract_R = fractional(tmp_R);

    if (N < today_.S + today_.I + today_.R) {
      if (fract_I < fract_S && fract_I < fract_R) {
        today_.I = std::floor(tmp_I);
      } else {
        if (fract_S < fract_I && fract_S < fract_R) {
          today_.S = std::floor(tmp_S);
        } else {
          today_.R = std::floor(tmp_R);
        }
      }
    }

    if (N > today_.S + today_.I + today_.R) {
      if (fract_I > fract_S && fract_I > fract_R) {
        today_.I = std::ceil(tmp_I);
      }

      else {
        if (fract_S > fract_I && fract_S > fract_R) {
          today_.S = std::ceil(tmp_S);
        } else {
          today_.R = std::ceil(tmp_R);
        }
      }
    }
    assert(N == today_.S + today_.I + today_.R);
  }
}
