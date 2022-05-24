#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "epidemic.hpp"

TEST_CASE("testing evolve") {
  SUBCASE("1 giorno, 10000 persone, 9980 s, 20 i, 0 r") {
    double gamma = 0.046 ;
    double beta = 0.056 ;
    double v_ratio = 0;
    Day today{9980, 20, 0};
    Epidemic epidemic{gamma, beta, v_ratio, today};
    epidemic.evolve(1);
    auto s = epidemic.state();
    CHECK(s.S == 9979);
     CHECK(s.I == 20);
      CHECK(s.R == 1);
  }
  SUBCASE("1 giorno,10000 persone, 9000 s, 1000 i, 0 r ") {
    double gamma = 0.046 ;
    double beta = 0.056 ;
    double v_ratio = 0;
    Day today{9000, 1000, 0};
    Epidemic epidemic{gamma, beta, v_ratio, today};
    epidemic.evolve(1);
    auto s = epidemic.state();
    CHECK(s.S == 8950);
     CHECK(s.I == 1004);
      CHECK(s.R == 46);
  }
  SUBCASE("10000 persone, 1 giorno, o s, 10000 i, 0 r") {
    double gamma = 0.046 ;
    double beta = 0.056 ;
    double v_ratio = 0;
    Day today{0, 10000, 0};
    Epidemic epidemic{gamma, beta, v_ratio, today};
    epidemic.evolve(1);
    auto s = epidemic.state();
    CHECK(s.S == 0);
     CHECK(s.I == 9540);
      CHECK(s.R == 460);
  }
  SUBCASE("10000 persone,1 giorno, 0 s, 0 i, 10000 r ") {
    double gamma = 0.046 ;
    double beta = 0.056 ;
    double v_ratio = 0;
    Day today{0, 0, 10000};
    Epidemic epidemic{gamma, beta, v_ratio, today};
    epidemic.evolve(1);
    auto s = epidemic.state();
    CHECK(s.S == 0);
     CHECK(s.I == 0);
      CHECK(s.R == 10000);
  }
  SUBCASE("10000 persone, 1 giorno, 9980 s, 20 i, 0 r") {
    double gamma =0.1 ;
    double beta = 0.3 ;
    double v_ratio = 0;
    Day today{9980, 20, 0};
    Epidemic epidemic{gamma, beta, v_ratio, today};
    epidemic.evolve(1);
    auto s = epidemic.state();
    CHECK(s.S == 9974 );
     CHECK(s.I == 24 );
      CHECK(s.R == 2);
  }
  SUBCASE("100000 persone, 2 giorni, 9000 s, 1000 i, 0 r") {
    double gamma = 0.1 ;
    double beta = 0.3 ;
    double v_ratio = 0;
    Day today{9000, 1000, 0};
    Epidemic epidemic{gamma, beta, v_ratio, today};
    epidemic.evolve(2);
    auto s = epidemic.state();
    CHECK(s.S == 8424 );
     CHECK(s.I == 1359 );
      CHECK(s.R == 217 );
  }


}
