#include "epidemic.hpp"
#include <iostream>

int main() {
  Epidemic epidemic{0.56, 0.46, Day{100000, 100, 0}};
  std::cout << epidemic.state() << '\n';
  for (int i = 0; i != 20; i++) {
    epidemic.evolve(1);
    auto s = epidemic.state();
    std::cout << s << "  ";
  }
}