//qui definizioni di metodi e funzioni
#include "epidemic.hpp"



std::ostream& operator<<(std::ostream& os, Day const& d){
    return os << "S = " << d.S << ", I = " << d.I << ", R = " << d.R;
}

Day Epidemic::state(){ return today_; }

double Epidemic::getBeta(){ return beta_; }

double Epidemic::getGamma(){ return gamma_; }

Day Epidemic::evolve(int d){
    
}

