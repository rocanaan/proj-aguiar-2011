#ifndef SIMULADOR_H_
#define SIMULADOR_H_

#include <vector>
#include <queue>
#include <deque>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
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
		
		int total_clientes_servidos_uma_vez;
        int total_clientes_servidos_duas_vezes;
		
		/*
        Variaveis que auxiliarão no cálculo do numero medio de clientes em cada regiao do sistema,
        acumulando o produto N * tempo, onde N é o número de pessoas em cada região do sistema.
        Nq1 = Número de pessoas na fila de espera para receber o primeiro serviço
        Nq2 = Número de pessoas na fila de espera para receber o segundo serviço
        N1 = Número total de pessoas no sistema que ainda não receberam o primeiro serviço completo
        N2 = Número total de pessoas no sistema que já foram servidas uma vez, mas ainda não completaram o segundo serviço
        OBS em um dado instante: Ni = Nqi + 1, se houver um cliente vindo da fila i no servidor
                                 Ni = Nqi, caso contrário
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
		double acumula_quadradoW1;
        double acumula_quadradoW2;
		
		vector<double> E_Nq1;
		vector<double> E_Nq2;
		vector<double> E_N1;
		vector<double> E_N2;
		vector<double> E_W1;
		vector<double> E_T1;
		vector<double> E_W2;
		vector<double> E_T2;
		vector<double> V_W1;
		vector<double> V_W2;
    
    public:
		Simulador(double ptaxa_chegada, double ptaxa_servico, bool deterministico);
		~Simulador();	
		void Roda(int num_total_clientes, int rodada_atual, bool debug_eventos, bool deterministico, bool determina_transiente, bool dois_por_vez);
		void CalculaResultados(int n, int servidos1, double t, int rodada, bool debug_eventos);
		void LimpaResultadosParciais();
		void GeraDadosGrafico(int rodada, double pN1, double pN2, double pNq1, double pNq2, double pW1, double pW2, double pT1, double pT2, double pV_W1, double pV_W2);
		vector<double> GetE_Nq1();
		vector<double> GetE_Nq2();
		vector<double> GetE_N1();
		vector<double> GetE_N2();
		vector<double> GetE_W1();
		vector<double> GetE_T1();
		vector<double> GetE_W2();
		vector<double> GetE_T2();
		vector<double> GetV_W1();
		vector<double> GetV_W2();
};
      
#endif /*SIMULADOR_H_*/
