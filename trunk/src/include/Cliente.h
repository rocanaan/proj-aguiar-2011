#include <stdio.h>
#include <cstdlib>
#include <iostream>

using namespace std;


class Cliente{
      private:
            int id;
			int fila;
			bool interrompido;
			double tempo_restante;

      public:
			Cliente();
			Cliente(int pid,int pfila,bool pinterrompido);
			int GetFila();
			int SetFila(int pfila);	
			double GetTempoRestante();
			double SetTempoRestante(double ptempo_restante);
			bool VerificaInterrompido();
			bool FoiInterrompido();
};
      
