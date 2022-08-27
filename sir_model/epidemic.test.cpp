#include "epidemic.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>

TEST_CASE("testing evolve") {
  SUBCASE(
      "1 giorno, 10000 persone, 9980 s, 20 i, 0 r, epidemia in espansione") {
    try {
      double gamma = 0.046;
      double beta = 0.056;
      Day today{9980, 20, 0};
      Epidemic epidemic{beta, gamma, today};
      epidemic.evolve();
      auto s = epidemic.state();
      CHECK(s == Day{9979, 20, 1});
    } catch (std::runtime_error const& e) {
      std::cerr << e.what() << '\n';
    }
  }
  SUBCASE("0 giorni, 10000 persone, 9980 s, 20 i") {
    try {
      double gamma = 0.046;
      double beta = 0.056;
      Day today{9980, 20, 0};
      Epidemic epidemic{beta, gamma, today};
      auto s = epidemic.state();
      CHECK(s == Day{9980, 20, 0});
    } catch (std::runtime_error const& e) {
      std::cerr << e.what() << '\n';
    }
  }
  SUBCASE("10000 persone,1 giorno, 10 s, 0 i, 9990 r, epidemia arrestata") {
    try {
      double gamma = 0.046;
      double beta = 0.056;
      Day today{10, 0, 9990};
      Epidemic epidemic{beta, gamma, today};
      epidemic.evolve();
      auto s = epidemic.state();
      CHECK(s == Day{10, 0, 9990});
    } catch (std::runtime_error const& e) {
      std::cerr << e.what() << '\n';
    }
  }
  SUBCASE(
      "1 giorno,10000 persone, 9000 s, 1000 i, 0 r, epidemia in espansione ") {
    try {
      double gamma = 0.046;
      double beta = 0.056;
      Day today{9000, 1000, 0};
      Epidemic epidemic{beta, gamma, today};
      epidemic.evolve();
      auto s = epidemic.state();
      CHECK(s == Day{8950, 1004, 46});
    } catch (std::runtime_error const& e) {
      std::cerr << e.what() << '\n';
    }
  }
  SUBCASE(
      "1 giorno, 10000 persone, o s, 10000 i, 0 r, epidemia in espansione") {
    try {
      double gamma = 0.046;
      double beta = 0.056;
      Day today{0, 10000, 0};
      Epidemic epidemic{beta, gamma, today};
      epidemic.evolve();
      auto s = epidemic.state();
      CHECK(s == Day{0, 9540, 460});
    } catch (std::runtime_error const& e) {
      std::cerr << e.what() << '\n';
    }
  }

  SUBCASE(
      "10000 persone, 1 giorno, 9980 s, 20 i, 0 r, epidemia in espansione") {
    try {
      double gamma = 0.1;
      double beta = 0.3;
      Day today{9980, 20, 0};
      Epidemic epidemic{beta, gamma, today};
      epidemic.evolve();
      auto s = epidemic.state();
      CHECK(s == Day{9974, 24, 2});
    } catch (std::runtime_error const& e) {
      std::cerr << e.what() << '\n';
    }
  }
  SUBCASE(
      "100000 persone, 2 giorni, 9000 s, 1000 i, 0 r, epidemia in espansione") {
    try {
      double gamma = 0.1;
      double beta = 0.3;
      Day today{9000, 1000, 0};
      Epidemic epidemic{beta, gamma, today};
      epidemic.evolve();
      epidemic.evolve();
      auto s = epidemic.state();
      CHECK(s == Day{8424, 1359, 217});
    } catch (std::runtime_error const& e) {
      std::cerr << e.what() << '\n';
    }
  }
  SUBCASE(
      "100000 persone, 1 giorno, 1500 s, 8000 i, 500 r, epidemia in "
      "contrazione") {
    try {
      double gamma = 0.1;
      double beta = 0.3;
      Day today{1500, 8000, 500};
      Epidemic epidemic{beta, gamma, today};
      epidemic.evolve();
      auto s = epidemic.state();
      CHECK(s == Day{1140, 7560, 1300});
    } catch (std::runtime_error const& e) {
      std::cerr << e.what() << '\n';
    }
  }
  SUBCASE(
      "100000 persone, 1 giorno, 9000 s, 1000 i, 0 r, l'epidemia non inizia") {
    try {
      double gamma = 0.4;
      double beta = 0.2;
      Day today{9000, 1000, 0};
      Epidemic epidemic{beta, gamma, today};
      epidemic.evolve();
      auto s = epidemic.state();
      CHECK(s == Day{8820, 780, 400});
    } catch (std::runtime_error const& e) {
      std::cerr << e.what() << '\n';
    }
  }
  SUBCASE(
    "110 persone, 1 giorno, 22 s, 25 i, 63 r, caso particolare") {
      try {
      double gamma = 0.2;
      double beta = 0.5;
      Day today{22, 25, 63};
      Epidemic epidemic{beta, gamma, today};
      epidemic.evolve();
      auto s = epidemic.state();
      CHECK(s == Day{19, 23, 68});
    } catch (std::runtime_error const& e) {
      std::cerr << e.what() << '\n';
    }
  }
}
