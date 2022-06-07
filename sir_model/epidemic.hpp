#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

#include <ostream>

struct Day {
  int S;
  int I;
  int R;
};

inline bool operator==(Day const& d1, Day const& d2) {
  return d1.S == d2.S && d1.I == d2.I && d1.R == d2.R;
}

double fractional(double x);

class Epidemic {
  double gamma_{};
  double beta_{};
  Day today_{};

 public:
  explicit Epidemic(double beta, double gamma, Day today)
      : gamma_{gamma}, beta_{beta}, today_{today} {
    if (gamma < 0 || gamma > 1) {
      throw std::runtime_error(
          "Il parametro gamma deve essere compreso tra 0 e 1");
    }

    if (beta < 0 || beta > 1) {
      throw std::runtime_error(
          "Il parametro beta deve essere compreso tra 0 e 1");
    }

    if (today.S < 0 || today.I < 0 || today.R < 0) {
      throw std::runtime_error(
          "I valori iniziali di S, I, R non possono essere negativi");
    }

    if (beta < gamma || today.I <= 2) {
      throw std::runtime_error("L'epidemia non parte con i parametri inseriti");
    }
  };

  explicit Epidemic() = default;

  Day state() const;

  // evolves epidemic by a day
  void evolve();
};

#endif