#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "epidemic.hpp"

TEST_CASE("testing evolve") {
  SUBCASE("tot persone, tot giorni") {
    double gamma = 0.046 ;
    double beta = 0.056 ;
    double v_ratio = 0;
    Day today{9980, 20, 0};
    Epidemic epidemic{gamma, beta, v_ratio, today};
    epidemic.evolve(1);
    auto s = epidemic.state();
    CHECK(s == Day{9979, 20, 1});
  }


}
