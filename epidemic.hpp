#include <vector>

// vettore di giorni. In ogni giorno, c'è una struct (population) con S,I,R.
// verifico con assert che siano sempre maggiori di 0.
//  E se invece di un vettore di giorni, facessi come nel lab5 un evolve con
//  numero di giorni ?

struct population {
  int S;
  int I;
  int R;
};

class epidemic {
  double gamma;
  double beta;
  std::vector<population> days;
  population initial_population;

  public:
  epidemic(population initial_pop) : initial_population{initial_pop} {};  

  void evolution (int S0, int I0, int R0, double delta_t) {
    days[0]={S0,I0,R0};
  for (int i = 1; i != delta_t+1; ++i) {
    population p_before = days [i-1];
    population p= days[i];
    
      p.S = p_before.S -beta*(p_before.S/N)*p_before.I;
      
  };
};
};