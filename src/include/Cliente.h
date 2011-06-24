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
		//Informa a rodada que o cliente pertence, utilizado como modo de "colora��o"
		int rodada_pertencente;
		
		//Instante de chegada do cliente no sistema, na fila 1
		double instante_chegada1;
		//Instante em que o cliente chega na fila 2. � o mesmo instante em que acaba seu primeiro servi�o
		double instante_chegada2;
		//Instante em que acaba o segundo servi�o do cliente. � o instante em que ele � removido do sistema
		double instante_saida;
		//Dura��o do primeiro servi�o
		double duracao_primeiro_servico;
		//Dura��o do segundo servi�o
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
      
