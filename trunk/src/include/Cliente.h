#include <stdio.h>
#include <cstdlib>
#include <iostream>

using namespace std;


class Cliente{
      private:
              int id;
			  int fila;

      public:
			 Cliente();
			 Cliente(int pid,int pfila);
			 int GetFila();
			 int SetFila(int pfila);
};
      
