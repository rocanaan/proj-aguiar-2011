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
	
	// como vou passar quais serao as taxas de chegada e de servico, preciso ter aqui 2 instâncias do gerador.
	// e cada uma delas ter uma das taxas. Logo, seria bom o metodo inversa estar dentro da classe geradora e que a classe tivesse um construtor
	// que tivesse como parametro a taxa requisitada.
	
	//Se não usarmos 2 instâncias do Gerador vamos então ter as 2 taxas aqui que usamos em lugares diferentes do método Roda do Simulador
	taxa_chegada = ptaxa_chegada;
	taxa_servico = ptaxa_servico;
	
	//Coloca o primeiro evendo na heap de eventos
	filaEventos.push(Evento(nova_chegada,inversa2(taxa_chegada)));
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
		Evento eventoAtual = filaEventos.top();
		filaEventos.pop();
		tempo_atual=eventoAtual.getTempoAcontecimento();
		cout << "Evento sendo tratado: Evento do tipo " << eventoAtual.getTipo() << " no tempo " << tempo_atual << endl;
		
		if(eventoAtual.getTipo() == nova_chegada)
		{
			if(!servidor_vazio && cliente_em_servico.GetFila() == FILA_2)
			{
				// Remove o evento Termino de Servico do cliente atualmente em servico
				// Altere o tempo de servico do cliente_em_servico
				// Mova ele para a frente da fila 2
				Evento eventoDestruido = filaEventos.top();
				filaEventos.pop();
				cout << "        Evento sendo destruido: : Evento do tipo " << eventoDestruido.getTipo() << " marcado para " <<  eventoDestruido.getTempoAcontecimento()<< endl;
				fila2.push_front(cliente_em_servico);
				cout << "Boom! Headshot!" << endl;
			}
			
			Cliente clienteAtual = Cliente(id_proximo_cliente,FILA_1); // O novo cliente começa na fila 1
			id_proximo_cliente++;
			
			fila1.push(clienteAtual); // Coloca o novo cliente na fila 1
			
			//agendar evento de proxima nova_chegada
			Evento proxChegada = Evento(nova_chegada,tempo_atual+inversa2(taxa_chegada));
			filaEventos.push(proxChegada);
			cout << "       Agendando nova chegada para " << proxChegada.getTempoAcontecimento() << endl;
			
		}
		else if (eventoAtual.getTipo() == termino_de_servico)
		{
			if(cliente_em_servico.GetFila() == FILA_1)
			{
				fila2.push_front(cliente_em_servico);
				cliente_em_servico.SetFila(FILA_2);
				cout << "       Fim de servico na fila 1. Inserindo cliente na fila 2" << endl;
			}
			else
			{
				//acabou seus servicos, logo + um cliente servido totalmente
				cout  <<"       Fim de servico na fila 2. Removendo cliente do sistema" << endl;
				num_clientes_servidos++;
			}
			
			//
			servidor_vazio = true;
		}
		
		//Se não tem ninguem no servidor
		if(servidor_vazio == true)
		{
			//Fila 1 tem prioridade
			if(!fila1.empty())
			{
				cliente_em_servico = fila1.front();
				fila1.pop();
				
				servidor_vazio = false;
				
				//agendar evento de termino de servico
				Evento proxTerminoServico = Evento(termino_de_servico,tempo_atual+inversa2(taxa_servico));
				filaEventos.push(proxTerminoServico);
				cout << "       Agendando proximo termino de servico da fila 1 para " << proxTerminoServico.getTempoAcontecimento() << endl;;
				
			}
			else if(!fila2.empty())
			{
				cliente_em_servico = fila2.front();
				fila2.pop_front();
			
				servidor_vazio = false;
				
				//agendar evento de termino de servico
				Evento proxTerminoServico = Evento(termino_de_servico,tempo_atual+inversa2(taxa_servico));
				filaEventos.push(proxTerminoServico);
				cout << "       Agendando proximo termino de servico da fila 2 para " << proxTerminoServico.getTempoAcontecimento() << endl;
			}
		}
	}


}    

