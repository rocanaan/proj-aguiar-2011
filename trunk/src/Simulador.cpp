#include "include\Simulador.h"
#include <math.h>
#define FILA_1 1
#define FILA_2 2
#define INTERROMPIDO 1
#define N_INTERROMPIDO 0

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------Contrutores & Destrutor-----------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Simulador::Simulador(double ptaxa_chegada, double ptaxa_servico)
{
	
	// como vou passar quais serao as taxas de chegada e de servico, preciso ter aqui 2 inst�ncias do gerador.
	// e cada uma delas ter uma das taxas. Logo, seria bom o metodo inversa estar dentro da classe geradora e que a classe tivesse um construtor
	// que tivesse como parametro a taxa requisitada.
	
	//Se n�o usarmos 2 inst�ncias do Gerador vamos ent�o ter as 2 taxas aqui que usamos em lugares diferentes do m�todo Roda do Simulador
	taxa_chegada = ptaxa_chegada;
	taxa_servico = ptaxa_servico;
	
	gerador = new GeradorTaxaExponencial();
	
	//Coloca o primeiro evendo na heap de eventos
	filaEventos.push(Evento(nova_chegada,gerador->ExponencialInversa(taxa_chegada)));
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
//------------------------------------------Fun��es Membro-------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Fun��o principal do simulador, executa a simula��o
void Simulador::Roda(int num_total_clientes)   
{
	int num_clientes_servidos = 0;
	
	
	//Enquanto o n�mero total de clientes que queremos servir for maior que o n�mero de clientes j� servidos por completo, rodamos a simula��o
	while(num_total_clientes > num_clientes_servidos)
	{
	
		Evento evento_atual = filaEventos.top();//O primeiro evento � selecionado 
		filaEventos.pop();//Ele � retirado da Fila
		tempo_atual=evento_atual.getTempoAcontecimento();
		cout << "Evento sendo tratado: Evento do tipo " << evento_atual.getTipo() << " no tempo " << tempo_atual << endl;
		
		//Se o Evento, que est� sendo tratado no momento, for do tipo nova_chegada
		if(evento_atual.getTipo() == nova_chegada)
		{
			//Condi��o para tratar a interrup��o presente no sistema.
			//Se o servidor estiver ocupado e este cliente for da fila 2 ent�o o cliente que acabou de chegar ir� interromper este servi�o
			if(!servidor_vazio && cliente_em_servico.GetFila() == FILA_2)
			{
				Evento evento_destruido = filaEventos.top(); //Guardamos o Evento a ser destruido
				filaEventos.pop();//Remove o Evento de T�rmino de servi�o gerado por este cliente da fila 2 ( ele vai sempre ser o top)
				cout << "        Evento sendo destruido: : Evento do tipo " << evento_destruido.getTipo() << " marcado para " <<  evento_destruido.getTempoAcontecimento()<< endl;
				
				cliente_em_servico.FoiInterrompido();//Marca o cliente como sendo um cliente Interrompido
				cliente_em_servico.SetTempoRestante(evento_destruido.getTempoAcontecimento() - tempo_atual);//O tempo restante para finalizar seu servico � guardado
				
				fila2.push_front(cliente_em_servico); //Cliente que foi interrompido volta a ser o primeiro da fila 2.
				servidor_vazio = true; //Deixa o servidor vazio
				cout << "Boom! Headshot!" << endl;
			}
			
			Cliente cliente_atual = Cliente(id_proximo_cliente,FILA_1,N_INTERROMPIDO); //O novo cliente come�a na fila 1
			id_proximo_cliente++; 
			
			fila1.push(cliente_atual); //Coloca o novo cliente na fila 1
			
			Evento proxChegada = Evento(nova_chegada,tempo_atual+gerador->ExponencialInversa(taxa_chegada));//Agenda o Evento para a pr�xima chegada
			filaEventos.push(proxChegada);
			cout << "       Agendando nova chegada para " << proxChegada.getTempoAcontecimento() << endl;
			
		}//Se o Evento, que est� sendo tratado no momento, for do termino_de_servico
		else if (evento_atual.getTipo() == termino_de_servico)
		{
			if(cliente_em_servico.GetFila() == FILA_1)
			{
				cliente_em_servico.SetFila(FILA_2);//O cliente que ir� terminar o servi�o agora � definido como da fila 2
				fila2.push(cliente_em_servico);// Coloca o cliente na fila 2
				cout << "       Fim de servico na fila 1. Inserindo cliente na fila 2" << endl;
			}
			else
			{
				//Acabou os 2 servi�os do cliente, logo marcamos mais um cliente servido totalmente
				cout  <<"       Fim de servico na fila 2. Removendo cliente do sistema" << endl;
				num_clientes_servidos++;
			}
			
			//
			servidor_vazio = true;//Como alguem foi servido marcamos o servidor como vazio
		}
		
		//Se n�o tem ninguem no servidor
		if(servidor_vazio == true)
		{
			//Fila 1 tem prioridade
			if(!fila1.empty())
			{
				cliente_em_servico = fila1.front();//O primeiro cliente da fila 1 entra em servico
				fila1.pop();//O cliente � removido da fila 1
				
				servidor_vazio = false;//O servidor agora est� ocupado
				
				Evento proxTerminoServico = Evento(termino_de_servico,tempo_atual+gerador->ExponencialInversa(taxa_servico));//Agendar evento de termino de servico
				filaEventos.push(proxTerminoServico);
				cout << "       Agendando proximo termino de servico da fila 1 para " << proxTerminoServico.getTempoAcontecimento() << endl;;
				
			}
			else if(!fila2.empty())
			{
				cliente_em_servico = fila2.front();
				fila2.pop_front();
			
				servidor_vazio = false;
				//Se o cliente, que veio da fila 2, n�o foi interrompido, gere para ele o seu tempo de servi�o
				if(cliente_em_servico.VerificaInterrompido() == N_INTERROMPIDO) 
				{
					Evento proxTerminoServico = Evento(termino_de_servico,tempo_atual+gerador->ExponencialInversa(taxa_servico));//Agenda evento de termino de servico
					filaEventos.push(proxTerminoServico);
					cout << "       Agendando proximo termino de servico da fila 2 para " << proxTerminoServico.getTempoAcontecimento() << endl;
				}

				else 
				{
					Evento proxTerminoServico = Evento(termino_de_servico,tempo_atual+cliente_em_servico.GetTempoRestante());//Agenda evento de termino de servico, com o tempo restante de servico do cliente que foi interrompido
					filaEventos.push(proxTerminoServico);
					cout << "(Evento j� foi interrompido alguma vez)Agendando proximo termino de servico da fila 2 para " << proxTerminoServico.getTempoAcontecimento() << endl;
				}
				

			}
			cout << "            Fila do cliente em servico:" << cliente_em_servico.GetFila() << endl;
		}
	}


}    

