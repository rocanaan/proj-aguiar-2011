#include <stdio.h>
#include <cstdlib>
#include <iostream>

using namespace std;
enum EnumTipo{nova_chegada,termino_de_servico};

class Evento{
      private:
              EnumTipo tipo;
              double tempo_chegada;
      
      public:
             Evento(EnumTipo ptipo, double ptempo_acontecimento);
             EnumTipo getTipo();
             double getTempoAcontecimento();
             ostream& imprime( ostream& o );
};
      
