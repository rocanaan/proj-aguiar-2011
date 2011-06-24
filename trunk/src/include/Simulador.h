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
		double cliente_W1;
		double cliente_W2;
		
		/*
        Variaveis que auxiliar�o no c�lculo do numero medio de clientes em cada regiao do sistema,
        acumulando o produto N * tempo, onde N � o n�mero de pessoas em cada regi�o do sistema.
        Nq1 = N�mero de pessoas na fila de espera para receber o primeiro servi�o
        Nq2 = N�mero de pessoas na fila de espera para receber o segundo servi�o
        N1 = N�mero total de pessoas no sistema que ainda n�o receberam o primeiro servi�o completo
        N2 = N�mero total de pessoas no sistema que j� foram servidas uma vez, mas ainda n�o completaram o segundo servi�o
        OBS em um dado instante: Ni = Nqi + 1, se houver um cliente vindo da fila i no servidor
                                 Ni = Nqi, caso contr�rio
        */
        double Nq1_parcial;
		double Nq2_parcial;
		double N1_parcial;
		double N2_parcial;
		
		/*
		Acumuladores das informacoes dos clientes
		*/
		double acumulaW1;
	    double acumulaT1;
        double acumulaW2;
        double acumulaT2;
    
    public:
		Simulador(double ptaxa_chegada, double ptaxa_servico);
		~Simulador();	
		void Roda(int num_total_clientes, int rodada_atual);
		void ImprimeResultados(int n, int servidos1, double t, int rodada);
};
      
#endif /*SIMULADOR_H_*/
