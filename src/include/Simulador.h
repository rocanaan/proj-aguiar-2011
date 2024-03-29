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
#include "GeradorTempoExponencial.h"

using namespace std;

class Simulador{
    private:
		/*
			Fila de prioridade para podermos ordenar os eventos a partir de seu tempo de acontecimento
		*/
		priority_queue<Evento, vector<Evento>, greater<Evento> > filaEventos;
		queue<Cliente> fila1;
		/*
			Foi utillizado deque para podermos mover um cliente de volta para a frente da fila 2 sem dificuldades
		*/
		deque<Cliente> fila2;
	
		GeradorTempoExponencial* gerador;
	
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
		Simulador();
		Simulador(double ptaxa_chegada, double ptaxa_servico, bool deterministico, bool dois_por_vez, bool interrupcao_forcada, int semente);
		~Simulador();	
		void Roda(int num_total_clientes, int rodada_atual, bool debug, bool deterministico, bool determina_transiente, bool dois_por_vez, string nome_pasta, bool guardar_estatisticas,bool interrupcao_forcada, bool mostrar_resultados);
		void CalculaResultados(int n, int servidos1, double t, int rodada, bool mostrar_resultados, string nome_pasta, bool guardar_estatisticas);
		void LimpaResultadosParciais();
		void Setup(int semente, bool deterministico);
		void GeraDadosGrafico(int rodada, double pN1, double pN2, double pNq1, double pNq2, double pW1, double pW2, double pT1, double pT2, double pV_W1, double pV_W2, string nome_pasta);
		Evento RemoveTerminoServico();
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
