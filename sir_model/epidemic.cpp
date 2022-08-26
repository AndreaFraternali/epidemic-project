#include "epidemic.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

double fractional(double x) { return x - std::floor(x); }

Day Epidemic::state() const { return today_; }

void Epidemic::rounding_int(double tmp_S, double tmp_I, double tmp_R, double const N) // Turning variables from continuos to discrete
{ 
  double fract_S = fractional(tmp_S);
  double fract_I = fractional(tmp_I);
  double fract_R = fractional(tmp_R);

  today_.S = std::round(tmp_S);
  today_.I = std::round(tmp_I);
  today_.R = std::round(tmp_R);

  std::vector<double> sir {fract_S, fract_I, fract_R};
  auto minimum = std::min_element(sir.begin(), sir.end());
  if (N < today_.S + today_.I + today_.R) {
    if (fract_I == *minimum) {
      today_.I = std::floor(tmp_I);
    } else {
      if (fract_S == *minimum) {
        today_.S = std::floor(tmp_S);
      } else {
        today_.R = std::floor(tmp_R);
      }
    }
  }
  
  auto maximum = std::max_element(sir.begin(), sir.end());
  if (N > today_.S + today_.I + today_.R) {
    if (fract_I == *maximum) {
      today_.I = std::ceil(tmp_I);
    }

    else {
      if (fract_S == *maximum) {
        today_.S = std::ceil(tmp_S);
      } else {
        today_.R = std::ceil(tmp_R);
      }
    }
  }
}

void Epidemic::evolve() {
  double const N = today_.S + today_.R + today_.I;

  auto yesterday = today_;

  double tmp_S = yesterday.S - beta_ * (yesterday.S / N) * yesterday.I;
  double tmp_I = yesterday.I + beta_ * (yesterday.S / N) * yesterday.I -
                 gamma_ * yesterday.I;
  double tmp_R = yesterday.R + gamma_ * yesterday.I;

  rounding_int(tmp_S, tmp_I, tmp_R,  N);

  assert(today_.S >= 0);
  assert(today_.I >= 0);
  assert(today_.R >= 0);
  assert(N == today_.S + today_.I + today_.R);
}