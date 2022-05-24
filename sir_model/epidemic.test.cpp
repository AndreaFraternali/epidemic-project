#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "epidemic.hpp"

TEST_CASE("testing evolve") {
  SUBCASE("1 giorno, 10000 persone, 9980 s, 20 i, 0 r, epidemia in espansione") {
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
  SUBCASE("0 giorni, 10000 persone, 9980 s, 20 i, 0 r") {
    double gamma = 0.046 ;
    double beta = 0.056 ;
    double v_ratio = 0;
    Day today{9980, 20, 0};
    Epidemic epidemic{gamma, beta, v_ratio, today};
    epidemic.evolve(0);
    auto s = epidemic.state();
    CHECK(s.S == 9980);
     CHECK(s.I == 20);
      CHECK(s.R == 0);
  }
  SUBCASE("1 giorno,10000 persone, 9000 s, 1000 i, 0 r, epidemia in espansione ") {
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
  SUBCASE("10000 persone, 1 giorno, o s, 10000 i, 0 r, epidemia in espansione") {
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
  SUBCASE("10000 persone,1 giorno, 10 s, 0 i, 9990 r, epidemia arrestata") {
    double gamma = 0.046 ;
    double beta = 0.056 ;
    double v_ratio = 0;
    Day today{10, 0, 9990};
    Epidemic epidemic{gamma, beta, v_ratio, today};
    epidemic.evolve(1);
    auto s = epidemic.state();
    CHECK(s.S == 10 );
     CHECK(s.I == 0);
      CHECK(s.R == 9990);
  }

  SUBCASE("10000 persone, 1 giorno, 9980 s, 20 i, 0 r, epidemia in espansione") {
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
  SUBCASE("100000 persone, 2 giorni, 9000 s, 1000 i, 0 r, epidemia in espansione") {
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
  SUBCASE("100000 persone, 1 giorno, 1500 s, 8000 i, 500 r, epidemia in contrazione") {
    double gamma = 0.1 ;
    double beta = 0.3 ;
    double v_ratio = 0;
    Day today{1500, 8000, 500};
    Epidemic epidemic{gamma, beta, v_ratio, today};
    epidemic.evolve(1);
    auto s = epidemic.state();
    CHECK(s.S == 1140 );
     CHECK(s.I == 7560 );
      CHECK(s.R == 1300 );
  }
  SUBCASE("100000 persone, 1 giorno, 9000 s, 1000 i, 0 r, l'epidemia non inizia") {
    double gamma = 0.4;
    double beta = 0.2;
    double v_ratio = 0;
    Day today{9000, 1000, 0};
    Epidemic epidemic{gamma, beta, v_ratio, today};
    epidemic.evolve(1);
    auto s = epidemic.state();
    CHECK(s.S == 8820 );
     CHECK(s.I == 780 );
      CHECK(s.R == 400 );
  }




}
