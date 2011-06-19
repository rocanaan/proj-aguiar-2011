#ifndef SIMULADOR_H_
#define SIMULADOR_H_

#include <vector>
#include <queue>
#include <deque>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "Cliente.h"
#include "Evento.h"
#include "GeradorTaxaExponencial.h"

using namespace std;

class Simulador{
    private:
		priority_queue<Evento, vector<Evento>, greater<Evento> > filaEventos;//Fila de prioridade para podermos ordenar os eventos a partir de seu tempo de acontecimento
		queue<Cliente> fila1;
		deque<Cliente> fila2;//Foi utillizado deque para podermos mover um cliente de volta para a frente da fila 2 sem dificuldades
	
		GeradorTaxaExponencial* gerador;
	
		double tempo_atual;
		Cliente cliente_em_servico;
		bool servidor_vazio;
		int id_proximo_cliente;
		double taxa_chegada;
		double taxa_servico;
    
    public:
		Simulador(double ptaxa_chegada, double ptaxa_servico);
		~Simulador();	
		void Roda(int num_total_clientes);
};
      
#endif /*SIMULADOR_H_*/
