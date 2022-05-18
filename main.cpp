#include "epidemic.hpp"

#include <iostream>
#include <iomanip>

int main() {
  Epidemic epidemic{0.0117399, 0.19317, Day{100000, 3, 0}};
  std::cout << epidemic.state() << std::setw(10) << "day 1" << '\n';
  for (int i = 0; i != 40; i++) {
    epidemic.evolve(1);
    auto s = epidemic.state();
    std::cout << s << std::setw(10) << "day " << i + 2 << '\n';
  }
}