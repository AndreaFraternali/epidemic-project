
//uso random per mettere un suscettibile in un punto a caso (se si può fare)
//uso random per confrontarlo con probabilità gamma di infettarsi
//usiamo n/8 * beta probabilità di infettarsi con n numero di infetti intorno
//se volessimo fare un test, solo griglia con evolve(0) che restituisce se stessa
#include "automaton.hpp"
#include <random>

std::vector<Cell> Grid::state() { return grid_; }


void Grid::evolve(int d){
    for(int j=0; j!=heigth_ ;++j ){ //ciclo for sulle righe (ho messo j perchè nella foto è j l'indice di riga)
        for(int i=0; i!=width_ ;++i ){ //ciclo for per ogni cella della riga (ho messo i perchè nella foto è i l'indice di colonna)
        
        } 
    }
}