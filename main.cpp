#include "epidemic.hpp"
#include <iostream>
#include <iomanip>

int main() {
  Epidemic epidemic{0.0117399, 0.19317, Day{10000, 2, 0}};
  std::cout << epidemic.state() << '\n';
  for (int i = 0; i != 40; i++) {
    epidemic.evolve(1);
    auto s = epidemic.state();
    std::cout << s << std::setw(14) << "day " << i + 1 << '\n';
  }
}