#include "epidemic.hpp"
#include <iostream>

int main() {
  Epidemic epidemic{0.50, 0.60, Day{1., 1., 0}};
  std::cout << epidemic.state() << '\n';
  for (int i = 0; i != 20; i++) {
    epidemic.evolve(1);
    auto s = epidemic.state();
    std::cout << s << '\n';
  }
}