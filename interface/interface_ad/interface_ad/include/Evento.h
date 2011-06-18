#ifndef EVENTO_H_
#define EVENTO_H_

#include <stdio.h>
#include <cstdlib>
#include <iostream>

using namespace std;
enum EnumTipo{nova_chegada,termino_de_servico};

class Evento{
      private:
              EnumTipo tipo;
              double tempo_acontecimento;
      
      public:
             Evento(EnumTipo ptipo, double ptempo_acontecimento);
             EnumTipo getTipo();
             double getTempoAcontecimento() const;
             ostream& imprime( ostream& o );
};

#endif EVENTO_H_
      
