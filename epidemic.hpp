#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

#include <vector>
#include <ostream>
// vettore di giorni. In ogni giorno, c'è una struct (population) con S,I,R.
// verifico con assert che siano sempre maggiori di 0.
//  E se invece di un vettore di giorni, facessi come nel lab5 un evolve con
//  numero di giorni?

struct day {
  int S;
  int I;
  int R;
};

std::ostream& operator<<(day const& d, std::ostream& os){
  return os << "S : " << d.S << ", I : " << d.I << ", R : " << d.R;
}

// class epidemia {
//   std::vector<day> days(double delta_t);

//   for (int i = 0; i != delta_t; ++i) {
//     if (i = 0) {
//       days[0] = {int S0, int I0, int R0};
//     } 
//     else {
//     }
//   }
// };


#endif
