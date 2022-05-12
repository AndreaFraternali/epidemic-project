//qui definizioni di classi e dichiarazioni di metodi e funzioni 
//io userei _ finale per le variabili membro, classi user-defined si scrivono con iniziale maiuscola

#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP


#include <ostream>

struct Day {
  int S;
  int I;
  int R;
};

std::ostream& operator<<(std::ostream& os, Day const& d);

class Epidemic {

  double gamma_{};
  double beta_{};
  Day today_{};

  public:
  explicit Epidemic(double gamma, double beta, Day today) : gamma_{gamma}, beta_{beta}, today_{today} {};  

  Day state(); 

  double getGamma();
  double getBeta();

  //ritorna lo stato dell'epidemia al giorno today + d
  Day evolve(int const d);
  
};



#endif