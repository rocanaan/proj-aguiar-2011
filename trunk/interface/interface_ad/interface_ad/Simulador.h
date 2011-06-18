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

#define FILA_1 1
#define FILA_2 2
#define INTERROMPIDO 1
#define N_INTERROMPIDO 0
using namespace std;


//Redefinição do operador > para podermos usar a priority_queue corretamente, ou seja, ordenando pelo tempo de acontecimento
bool operator > (const Evento& evento1, const Evento& evento2)
{
    return (evento1.getTempoAcontecimento() > evento2.getTempoAcontecimento());                                                                 
}


class Simulador{
    private:
		priority_queue<Evento, vector<Evento>, greater<Evento> > filaEventos;//Fila de prioridade para podermos ordenar os eventos a partir de seu tempo de acontecimento
		queue<Cliente> fila1;
		deque<Cliente> fila2;//Foi utillizado deque para podermos mover um cliente de volta para a frente da fila 2 sem dificuldades
	
	
	
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
      
#endif SIMULADOR_H_
