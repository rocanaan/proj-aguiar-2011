#include "include\Simulador.h"
#include "include\GeradorNumerosAleatorios.h"
#include <math.h>
#define FILA_1 1
#define FILA_2 2

using namespace std;

// defini aqui de novo com outro nome so pra nao reclamar de definicao, n queria me preocupar com fazer a main e o simulador verem a inversa
double inversa2(double taxa)
{
	return (-1) * (log(1 - GeradorNumerosAleatorios::GetInstance()->Random()) / taxa);
}



Simulador::Simulador(double ptaxa_chegada, double ptaxa_servico)
{
	
	// como vou passar quais serao as taxas de chegada e de servico, preciso ter aqui 2 inst�ncias do gerador.
	// e cada uma delas ter uma das taxas. Logo, seria bom o metodo inversa estar dentro da classe geradora e que a classe tivesse um construtor
	// que tivesse como parametro a taxa requisitada.
	
   //Coloca o primeiro evendo na heap de eventos
   filaEventos.push(Evento(nova_chegada,inversa2(1)));
   servidor_vazio = true;
   id_proximo_cliente = 0;
   tempo_atual=0;
}      

void Simulador::Roda(int num_total_clientes)   
{
	int num_clientes_servidos = 0;
	
	while(num_total_clientes > num_clientes_servidos)
	{
		//Pegar o primeiro evento da heap
		// tirar ele da heap e dar a ele o tempo como o tempo atual
		Evento e = filaEventos.top();
		filaEventos.pop();
		tempo_atual=e.getTempoAcontecimento();
		cout << e.imprime(cout) << endl;
		
		if(1/*tipo do evento == nova_chegada, por enquanto botei 1*/)
		{
			if(!servidor_vazio && cliente_em_servico.GetFila() == FILA_2)
			{
				// Remove o evento Termino de Servico do cliente atualmente em servico
				// Altere o tempo de servico do cliente_em_servico
				// Mova ele para a frente da fila 2
				fila2.push_front(cliente_em_servico);
			}
			
			Cliente clienteAtual = Cliente(id_proximo_cliente,FILA_1); // O novo cliente come�a na fila 1
			id_proximo_cliente++;
			
			fila1.push(clienteAtual); // Coloca o novo cliente na fila 1
			
			//agendar evento de proxima nova_chegada
			filaEventos.push(Evento(nova_chegada,tempo_atual+inversa2(0.5)));
			
		}
		else if (1/*tipo de evento == termino_de_servico, por enquanto botei 1*/)
		{
			if(cliente_em_servico.GetFila() == FILA_1)
			{
				fila2.push_front(cliente_em_servico);
				cliente_em_servico.SetFila(FILA_2);
			}
			else
			{
				//acabou seus servicos, logo + um cliente servido totalmente
				num_clientes_servidos++;
			}
			
			//
			servidor_vazio = true;
		}
		
		//Se n�o tem ninguem no servidor
		if(servidor_vazio == true)
		{
			//Fila 1 tem prioridade
			if(!fila1.empty())
			{
				cliente_em_servico = fila1.front();
				fila1.pop();
				
				servidor_vazio = false;
				
				//agendar evento de termino de servico
			}
			else if(!fila2.empty())
			{
				cliente_em_servico = fila2.front();
				fila2.pop_front();
			
				servidor_vazio = false;
				
				//agendar evento de termino de servico
			}
		}
	}


}    
