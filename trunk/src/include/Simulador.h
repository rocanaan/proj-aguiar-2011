#include <queue>
#include <deque>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "Cliente.h"

using namespace std;


class Simulador{
      private:
        // tenho que ter a fila de heap de eventos 
         
		queue<Cliente> fila1;
		// Foi utillizado deque para podermos mover um cliente de volta para a frente da fila 2 sem dificuldades
		deque<Cliente> fila2;
		
		
		
		double tempo_atual;
		Cliente cliente_em_servico;
		bool servidor_vazio;
		int id_proximo_cliente;

      public:
        Simulador(double ptaxa_chegada, double ptaxa_servico);		   
		void Roda(int num_total_clientes);
};
      
