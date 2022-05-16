//qui definizioni di classi e dichiarazioni di metodi e funzioni 
//io userei _ finale per le variabili membro, classi user-defined si scrivono con iniziale maiuscola
#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

#include <stdexcept>
#include <ostream>

struct Day {
  double S;
  double I;
  double R;
};

std::ostream& operator<<(std::ostream& os, Day const& d);

class Epidemic {

  double gamma_{};
  double beta_{};
  Day today_{};

  public:
  explicit Epidemic(double gamma, double beta, Day today) : gamma_{gamma}, beta_{beta}, today_{today} {

    if(gamma < 0 || gamma > 1){
      throw std::runtime_error{"Gamma parameter must be between 0 and 1"};
    }

    if(beta < 0 || beta > 1){
      throw std::runtime_error{"Beta parameter must be between 0 and 1"};
    }

    if(today_.I < 0 || today_.S < 0 || today_.R < 0){
      throw std::runtime_error{"SIR model parameters cannot be negative"};
    }

  };  

  Day state(); 

  double getGamma();
  double getBeta();

  //ritorna lo stato dell'epidemia al giorno today + d
  void evolve(int const d);
  
};



#endif