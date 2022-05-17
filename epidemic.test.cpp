#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "epidemic.hpp"

TEST_CASE("testing evolve") {
  SUBCASE("tot persone, tot giorni") {
    double gamma = ;
    double beta = ;
    Day today{};
    Epidemic epidemic{gamma, beta, today};
    epidemic.evolve();
    auto s = epidemic.state();
    CHECK(s == Day{});
  }
}
