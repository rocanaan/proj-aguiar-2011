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
		bool direto_ao_servidor;
		//Informa a rodada que o cliente pertence, utilizado como modo de "coloração"
		int rodada_pertencente;
		
		//Instante de chegada do cliente no sistema, na fila 1
		double instante_chegada1;
		//Instante em que o cliente chega na fila 2. É o mesmo instante em que acaba seu primeiro serviço
		double instante_chegada2;
		//Instante em que acaba o segundo serviço do cliente. É o instante em que ele é removido do sistema
		double instante_saida;
		//Duração do primeiro serviço
		double duracao_primeiro_servico;
		//Duração do segundo serviço
		double duracao_segundo_servico;

	public:
		Cliente();
		Cliente(int pid,double instante_chegada,int pfila, int rodada_atual);
		int GetID();
		int GetFila();
		int SetFila(int pfila);	
		double GetTempoRestante();
		double SetTempoRestante(double ptempo_restante);
		bool VerificaInterrompido();
		void Interromper();
		void SetDiretoAoServidor(bool pbool);
		bool GetDiretoAoServidor();
		int GetRodadaPertencente();

		void SetInstanteChegada2(double t);
		void SetInstanteSaida(double t);
		void SetDuracaoPrimeiroServico(double duracao);
		void SetDuracaoSegundoServico(double duracao);
		
		double W1();
		double T1();
		double W2();
		double T2();
};
      
