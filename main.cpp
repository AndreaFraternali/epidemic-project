#include "epidemic.hpp"

#include <iostream>
#include <iomanip>

int main() {
  Epidemic epidemic{0.0117399, 0.19317, 0.01, Day{1000000, 10, 0}};
  std::cout << epidemic.state() << '\n';
  for (int i = 0; i != 40; i++) {
    epidemic.evolve(1);
    auto s = epidemic.state();
    std::cout << s << std::setw(10) << "day " << i + 2 << '\n';
  }
}