#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

#include <stdexcept>
#include <vector>
#include <iostream>

struct Day
{
  int S;
  int I;
  int R;
};

inline bool operator==(Day const &d1, Day const &d2)
{
  return d1.S == d2.S && d1.I == d2.I && d1.R == d2.R;
}

inline std::ostream &operator<<(std::ostream &os, std::vector<Day> &ep)
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
double fractional(double x);

class Epidemic
{
  double beta_{};
  double gamma_{};
  Day today_{};

public:
  explicit Epidemic(double beta, double gamma, Day today)
      : beta_{beta}, gamma_{gamma}, today_{today}
  {
    if (gamma < 0 || gamma > 1)
    {
      throw std::runtime_error(
          "Il parametro gamma deve essere compreso tra 0 e 1");
    }

    if (beta < 0 || beta > 1)
    {
      throw std::runtime_error(
          "Il parametro beta deve essere compreso tra 0 e 1");
    }

    if (today.S < 0 || today.I < 0 || today.R < 0)
    {
      throw std::runtime_error(
          "I valori iniziali di S, I, R non possono essere negativi");
    }

    if (beta < gamma || today.I <= 2)
    {
      throw std::runtime_error("L'epidemia non parte con i parametri inseriti");
    }
  };

  Epidemic() = default;

  Day state() const;

  // evolves epidemic by a day
  void evolve();
  void rounding_int(double tmp_S, double tmp_I, double tmp_R, int const N);
};

#endif