#include <vector>
#include<random>

  enum class cella {S, I, R};

class griglia{
    int lato;
    std::vector<cella> riga;
    std::vector<std::vector<cella>> colonna; //perchè non posso fare vettore di righe?
    
    public: griglia(int lato_): lato(lato_)  {};
     
    for(int i=0, i<lato, ++i) {
    riga.push_back(cella::S);
    }
    
     

};