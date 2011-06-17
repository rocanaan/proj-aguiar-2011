#include "include\Simulador.h"
#include "include\GeradorNumerosAleatorios.h"
#include <math.h>
#define FILA_1 1
#define FILA_2 2
#define INTERROMPIDO 1
#define N_INTERROMPIDO 0

using namespace std;

//Defini aqui de novo com outro nome so pra nao reclamar de definicao, n queria me preocupar com fazer a main e o simulador verem a inversa
double inversa2(double taxa)
{
	return (-1) * (log(1 - GeradorNumerosAleatorios::GetInstance()->Random()) / taxa);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------Contrutores & Destrutor-----------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

Simulador::~Simulador()
{
	//Destrutor
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------Funções Membro-------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Função principal do simulador, executa a simulação
void Simulador::Roda(int num_total_clientes)   
{
	int num_clientes_servidos = 0;
	
	//Enquanto o número total de clientes que queremos servir for maior que o número de clientes já servidos por completo, rodamos a simulação
	while(num_total_clientes > num_clientes_servidos)
	{
	
		Evento eventoAtual = filaEventos.top();//O primeiro evento é selecionado 
		filaEventos.pop();//Ele é retirado da Fila
		tempo_atual=eventoAtual.getTempoAcontecimento();
		cout << "Evento sendo tratado: Evento do tipo " << eventoAtual.getTipo() << " no tempo " << tempo_atual << endl;
		
		//Se o Evento, que está sendo tratado no momento, for do tipo nova_chegada
		if(eventoAtual.getTipo() == nova_chegada)
		{
			//Condição para tratar a interrupção presente no sistema.
			//Se o servidor estiver ocupado e este cliente for da fila 2 então o cliente que acabou de chegar irá interromper este serviço
			if(!servidor_vazio && cliente_em_servico.GetFila() == FILA_2)
			{
				Evento eventoDestruido = filaEventos.top(); //Guardamos o Evento a ser destruido
				filaEventos.pop();//Remove o Evento de Término de serviço gerado por este cliente da fila 2 ( ele vai sempre ser o top)
				cout << "        Evento sendo destruido: : Evento do tipo " << eventoDestruido.getTipo() << " marcado para " <<  eventoDestruido.getTempoAcontecimento()<< endl;
				fila2.push_front(cliente_em_servico); //Cliente que foi interrompido volta a ser o primeiro da fila 2.
				servidor_vazio = true; //Deixa o servidor vazio
				cout << "Boom! Headshot!" << endl;
			}
			
			Cliente clienteAtual = Cliente(id_proximo_cliente,FILA_1,N_INTERROMPIDO); //O novo cliente começa na fila 1
			id_proximo_cliente++; 
			
			fila1.push(clienteAtual); //Coloca o novo cliente na fila 1
			
			Evento proxChegada = Evento(nova_chegada,tempo_atual+inversa2(taxa_chegada));//Agenda o Evento para a próxima chegada
			filaEventos.push(proxChegada);
			cout << "       Agendando nova chegada para " << proxChegada.getTempoAcontecimento() << endl;
			
		}//Se o Evento, que está sendo tratado no momento, for do termino_de_servico
		else if (eventoAtual.getTipo() == termino_de_servico)
		{
			if(cliente_em_servico.GetFila() == FILA_1)
			{
				cliente_em_servico.SetFila(FILA_2);//O cliente que irá terminar o serviço agora é definido como da fila 2
				fila2.push_front(cliente_em_servico);// Coloca o cliente na fila 2
				cout << "       Fim de servico na fila 1. Inserindo cliente na fila 2" << endl;
			}
			else
			{
				//Acabou os 2 serviços do cliente, logo marcamos mais um cliente servido totalmente
				cout  <<"       Fim de servico na fila 2. Removendo cliente do sistema" << endl;
				num_clientes_servidos++;
			}
			
			//
			servidor_vazio = true;//Como alguem foi servido marcamos o servidor como vazio
		}
		
		//Se não tem ninguem no servidor
		if(servidor_vazio == true)
		{
			//Fila 1 tem prioridade
			if(!fila1.empty())
			{
				cliente_em_servico = fila1.front();//O primeiro cliente da fila 1 entra em servico
				fila1.pop();//O cliente é removido da fila 1
				
				servidor_vazio = false;//O servidor agora está ocupado
				
				Evento proxTerminoServico = Evento(termino_de_servico,tempo_atual+inversa2(taxa_servico));//Agendar evento de termino de servico
				filaEventos.push(proxTerminoServico);
				cout << "       Agendando proximo termino de servico da fila 1 para " << proxTerminoServico.getTempoAcontecimento() << endl;;
				
			}
			else if(!fila2.empty())
			{
				cliente_em_servico = fila2.front();
				fila2.pop_front();
			
				servidor_vazio = false;
				
				Evento proxTerminoServico = Evento(termino_de_servico,tempo_atual+inversa2(taxa_servico));//Agenda evento de termino de servico
				filaEventos.push(proxTerminoServico);
				cout << "       Agendando proximo termino de servico da fila 2 para " << proxTerminoServico.getTempoAcontecimento() << endl;
			}
			cout << "            Fila do cliente em servico:" << cliente_em_servico.GetFila() << endl;
		}
	}


}    

