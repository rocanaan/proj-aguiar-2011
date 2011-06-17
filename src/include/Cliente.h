#include <stdio.h>
#include <cstdlib>
#include <iostream>

using namespace std;


class Cliente{
      private:
              int id;
			  int fila;
			  bool interrompido;

      public:
			 Cliente();
			 Cliente(int pid,int pfila,bool pinterrompido);
			 int GetFila();
			 int SetFila(int pfila);
			 bool FoiInterrompido();
};
      
