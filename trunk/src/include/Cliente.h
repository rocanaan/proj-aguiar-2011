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
		
		// instante de chegada do cliente no sistema, na fila 1
		double instante_chegada1;
		// instante em que o cliente chega na fila 2. � o mesmo instante em que acaba seu primeiro servi�o
		double instante_chegada2;
		// instante em que acaba o segundo servi�o do cliente. � o instante em que ele � removido do sistema
		double instante_saida;
		// dura��o do primeiro servi�o
		double duracao_primeiro_servico;
		// dura��o do segundo servi�o
		double duracao_segundo_servico;

	public:
		Cliente();
		Cliente(int pid,double instante_chegada,int pfila);
		int GetID();
		int GetFila();
		int SetFila(int pfila);	
		double GetTempoRestante();
		double SetTempoRestante(double ptempo_restante);
		bool VerificaInterrompido();
		void Interromper();
		void SetDiretoAoServidor(bool pbool);
		bool GetDiretoAoServidor();

		void SetInstanteChegada2(double t);
		void SetInstanteSaida(double t);
		void SetDuracaoPrimeiroServico(double duracao);
		void SetDuracaoSegundoServico(double duracao);
		
		double W1();
		double T1();
		double W2();
		double T2();
};
      
