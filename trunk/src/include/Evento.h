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
             Evento(EnumTipo ptipo, double ptempo_chegada);
             EnumTipo getTipo();
             double getTempoChegada();
             ostream& imprime( ostream& o );
};
      
