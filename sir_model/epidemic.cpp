#include "epidemic.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

double fractional(double x) { return x - std::floor(x); }

std::ostream &operator<<(std::ostream &os, std::vector<Day> &ep)
{
  int day_count = 1;
  for (Day day : ep)
  {
    std::cout << '\n' << "Day " << day_count << '\n';
    std::cout << "S = " << day.S << '\t' << "I = " << day.I << '\t' << "R = " << day.R << '\n';
    day_count++;
  }
  return os;
}
Day Epidemic::state() const { return today_; }

// Turning variables from continuos to discrete
void Epidemic::rounding_int(double tmp_S, double tmp_I, double tmp_R,
                            int const N)
{
  double fract_S = fractional(tmp_S);
  double fract_I = fractional(tmp_I);
  double fract_R = fractional(tmp_R);

  today_.S = std::round(tmp_S);
  today_.I = std::round(tmp_I);
  today_.R = std::round(tmp_R);

  std::vector<double> sir{fract_S, fract_I, fract_R};
  enum floor_or_ceil
  {
    S,
    I,
    R
  };

  auto minimum = std::min_element(sir.begin(), sir.end());
  if (N < today_.S + today_.I + today_.R)
  {
    if (fract_I == 0 || fract_R == 0 || fract_S == 0)
    { // dealing with a rare case
      tmp_S -= 0.1;
      tmp_I += 0.1;
      today_.S = std::round(tmp_S);
      today_.I = std::round(tmp_I);
      today_.R = std::ceil(tmp_R);
    }
    int cases = minimum - sir.begin(); // index of the min element
    switch (cases)
    {
    case floor_or_ceil::S:
      today_.S = std::floor(tmp_S);
      break;
    case floor_or_ceil::I:
      today_.I = std::floor(tmp_I);
      break;
    case floor_or_ceil::R:
      today_.R = std::floor(tmp_R);
      break;
    }
  }

  auto maximum = std::max_element(sir.begin(), sir.end());
  if (N > today_.S + today_.I + today_.R)
  {
    int cases = maximum - sir.begin(); // index of the max element
    switch (cases)
    {
    case floor_or_ceil::S:
      today_.S = std::ceil(tmp_S);
      break;
    case floor_or_ceil::I:
      today_.I = std::ceil(tmp_I);
      break;
    case floor_or_ceil::R:
      today_.R = std::ceil(tmp_R);
      break;
    }
  }
}

void Epidemic::evolve()
{
  double const N = today_.S + today_.R + today_.I;

  auto yesterday = today_;

  double tmp_S = yesterday.S - beta_ * (yesterday.S / N) * yesterday.I;
  double tmp_I = yesterday.I + beta_ * (yesterday.S / N) * yesterday.I -
                 gamma_ * yesterday.I;
  double tmp_R = yesterday.R + gamma_ * yesterday.I;

  rounding_int(tmp_S, tmp_I, tmp_R, N);

  assert(today_.S >= 0);
  assert(today_.I >= 0);
  assert(today_.R >= 0);
  assert(N == today_.S + today_.I + today_.R);
}