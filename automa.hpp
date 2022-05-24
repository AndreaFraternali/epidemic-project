#include <vector>
#include<random>

  enum class cella {S, I, R};

class griglia{
    int lato;
    std::vector<cella> riga;
    std::vector<std::vector<cella>> colonna;
};

