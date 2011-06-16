#include "include\Evento.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

    Evento::Evento(int t, double h){
                             this->tipo = t;
                             this->ptempo_acontecimento = h;
                             }
                             
          int Evento::getTipo(){
              return tipo;
              }
          double Evento::getTempoAcontecimento(){
                 return ptempo_acontecimento;
                 }
          ostream& Evento::imprime(ostream& o){
               o << "Evento do tipo " << tipo << " marcado para " << ptempo_acontecimento << endl;
               }
                             
             
             
