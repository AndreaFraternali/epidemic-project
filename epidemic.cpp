// qui definizioni di metodi e funzioni
#include "epidemic.hpp"

#include <cassert>
#include <iostream>
#include <cmath>

std::ostream& operator<<(std::ostream& os, Day const& d) {
  return os << "S = " << (int)d.S << ", I = " << (int)d.I << ", R = " << (int)d.R;
}

Day Epidemic::state() { return today_; }

double Epidemic::getBeta() { return beta_; }

double Epidemic::getGamma() { return gamma_; }

void Epidemic::evolve(int d) {
  double const N = today_.S + today_.R + today_.I;
  assert(N > 0);

  for (int i = 0; i != d; ++i) {
    auto yesterday = today_;
    today_.S = std::round(yesterday.S - beta_ * (yesterday.S / N) * yesterday.I);
    today_.I = std::round(yesterday.I + beta_ * (yesterday.S / N) * yesterday.I -
               gamma_ * yesterday.I);
    today_.R = std::round(yesterday.R + gamma_ * yesterday.I);  

    if(N < today_.S + today_.I + today_.R){
      double S_eccesso= yesterday.S - beta_ * (yesterday.S / N) * yesterday.I;
      double S_difetto= floor(S_eccesso);
      double I_eccesso= (yesterday.I + beta_ * (yesterday.S / N) * yesterday.I -
               gamma_ * yesterday.I);
      double I_difetto= floor(I_eccesso);         
      double R_eccesso= yesterday.R + gamma_ * yesterday.I;
      double R_difetto= floor(R_difetto);
      double S_decimale=S_eccesso-S_difetto;
      double I_decimale=I_eccesso-I_difetto;
      double R_decimale=R_eccesso-R_difetto;
      if(I_decimale < S_decimale && R_decimale) {today_.I=I_difetto;};
      if(S_decimale < I_decimale && R_decimale) {today_.S=S_difetto;};
      if(R_decimale < S_decimale && I_decimale) {today_.R=R_difetto;};
    };
   if(N > today_.S + today_.I + today_.R){
     double S_eccesso= yesterday.S - beta_ * (yesterday.S / N) * yesterday.I;
      double S_difetto= floor(S_eccesso);
      double I_eccesso= (yesterday.I + beta_ * (yesterday.S / N) * yesterday.I -
               gamma_ * yesterday.I);
      double I_difetto= floor(I_eccesso);         
      double R_eccesso= yesterday.R + gamma_ * yesterday.I;
      double R_difetto= floor(R_difetto);
      double S_decimale=S_eccesso-S_difetto;
      double I_decimale=I_eccesso-I_difetto;
      double R_decimale=R_eccesso-R_difetto;
      if(S_decimale > I_decimale && R_decimale) {today_.S=S_eccesso+1;};
      if(I_decimale > S_decimale && R_decimale) {today_.I=I_eccesso+1;};
      if(R_decimale > S_decimale && I_decimale) {today_.R=R_eccesso;};
    };
    
    if(N < today_.S + today_.I + today_.R){std::cout<<"aumento";};
    if(N > today_.S + today_.I + today_.R){std::cout<<"diminuisce";};

  }
}
