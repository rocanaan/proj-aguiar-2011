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
	
	// como vou passar quais serao as taxas de chegada e de servico, preciso ter aqui 2 instâncias do gerador.
	// e cada uma delas ter uma das taxas. Logo, seria bom o metodo inversa estar dentro da classe geradora e que a classe tivesse um construtor
	// que tivesse como parametro a taxa requisitada.
	
	//Se não usarmos 2 instâncias do Gerador vamos então ter as 2 taxas aqui que usamos em lugares diferentes do método Roda do Simulador
	taxa_chegada = ptaxa_chegada;
	taxa_servico = ptaxa_servico;
	
	gerador = new GeradorTaxaExponencial();
	
	//Coloca o primeiro evendo na heap de eventos
	filaEventos.push(Evento(nova_chegada,gerador->ExponencialInversa(taxa_chegada)));
	servidor_vazio = true;
	id_proximo_cliente = 0;
	tempo_atual=0;
	
	/*
    inicia as variaveis que acumulam o (numero de pessoas * tempo) de cada região do sistema
    */
	Nq1_parcial = 0;
	Nq2_parcial = 0;
	N1_parcial = 0;
	N2_parcial = 0;
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
	
		Evento evento_atual = filaEventos.top();//O primeiro evento é selecionado 
		filaEventos.pop();//Ele é retirado da Fila
		double tempo_desde_evento_anterior = evento_atual.getTempoAcontecimento()-tempo_atual;
		tempo_atual=evento_atual.getTempoAcontecimento();
		cout << "Evento sendo tratado: Evento do tipo " << evento_atual.getTipo() << " no tempo " << tempo_atual << endl;
		cout << "Status do sistema (antes de resolver o evento):" << endl;
		if(servidor_vazio)
		                  cout << "     O servidor esta vazio" << endl;
		else
		                  cout << "     Há 1 cliente em servico, vindo da fila " << cliente_em_servico.GetFila() <<endl;
		cout << "     Numero de pessoas na fila 1: " << fila1.size()  << endl;
        cout << "     Numero de pessoas na fila 2: " << fila2.size() << endl;
        
        
        /* Para cada uma das variaveis Nq1, Nq2, N1 e N2,
           calcula a "area sob a curva" desde o ultimo evento, multiplicando 
           o valor da variavel pelo tamanho do intervalo entre o evento anterior
           e o evento atual.
           Como entre eventos nada muda no servidor, cada uma dessas variaveis
           permaneceu constante
                      Nq1 e Nq2 sao o numero de pessoas nas filas de espera 1 e 2, respectivamente
                      N1 e N2 sao o numero de pessoas esperando cada tipo de servico na fila
                      Ni = Nqi + 1 se houver um cliente vindo da fila i no servidor
                      Ni = Nqi caso contrario
           No final da simulacao, teremos a area sob a curva de cada uma dessas variaveis.
           Faltara dividir pelo tempo total decorrido para calcular a media.
        */
        Nq1_parcial += fila1.size()*tempo_desde_evento_anterior;
        Nq2_parcial += fila2.size()*tempo_desde_evento_anterior;
        if (!servidor_vazio){
           if (cliente_em_servico.GetFila() == 1){
              N1_parcial += (1+fila1.size())*tempo_desde_evento_anterior;
              N2_parcial += fila2.size()*tempo_desde_evento_anterior;
           }
           else{
                N1_parcial += fila1.size()*tempo_desde_evento_anterior;
                N2_parcial += (1+fila2.size())*tempo_desde_evento_anterior;
           }
        }
        else{
             N1_parcial += fila1.size()*tempo_desde_evento_anterior;
             N2_parcial += fila2.size()*tempo_desde_evento_anterior;
        }                             
 
		//Se o Evento, que está sendo tratado no momento, for do tipo nova_chegada
		if(evento_atual.getTipo() == nova_chegada)
		{
			//Condição para tratar a interrupção presente no sistema.
			//Se o servidor estiver ocupado e este cliente for da fila 2 então o cliente que acabou de chegar irá interromper este serviço
			if(!servidor_vazio && cliente_em_servico.GetFila() == FILA_2)
			{
				Evento evento_destruido = filaEventos.top(); //Guardamos o Evento a ser destruido
				filaEventos.pop();//Remove o Evento de Término de serviço gerado por este cliente da fila 2 ( ele vai sempre ser o top)
				cout << "          Evento sendo destruido: : Evento do tipo " << evento_destruido.getTipo() << " marcado para " <<  evento_destruido.getTempoAcontecimento()<< endl;
				
				cliente_em_servico.FoiInterrompido();//Marca o cliente como sendo um cliente Interrompido
				cliente_em_servico.SetTempoRestante(evento_destruido.getTempoAcontecimento() - tempo_atual);//O tempo restante para finalizar seu servico é guardado
				
				fila2.push_front(cliente_em_servico); //Cliente que foi interrompido volta a ser o primeiro da fila 2.
				servidor_vazio = true; //Deixa o servidor vazio
			}
			
			Cliente cliente_atual = Cliente(id_proximo_cliente,FILA_1,N_INTERROMPIDO); //O novo cliente começa na fila 1
			id_proximo_cliente++; 
			
			fila1.push(cliente_atual); //Coloca o novo cliente na fila 1
			
			Evento proxChegada = Evento(nova_chegada,tempo_atual+gerador->ExponencialInversa(taxa_chegada));//Agenda o Evento para a próxima chegada
			filaEventos.push(proxChegada);
			cout << "          Agendando nova chegada para " << proxChegada.getTempoAcontecimento() << endl;
			
		}//Se o Evento, que está sendo tratado no momento, for do termino_de_servico
		else if (evento_atual.getTipo() == termino_de_servico)
		{
			if(cliente_em_servico.GetFila() == FILA_1)
			{
				cliente_em_servico.SetFila(FILA_2);//O cliente que irá terminar o serviço agora é definido como da fila 2
				fila2.push_back(cliente_em_servico);// Coloca o cliente na fila 2
				cout << "          Fim de servico na fila 1. Inserindo cliente na fila 2" << endl;
			}
			else
			{
				//Acabou os 2 serviços do cliente, logo marcamos mais um cliente servido totalmente
				cout  <<"          Fim de servico na fila 2. Removendo cliente do sistema" << endl;
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
				
				Evento proxTerminoServico = Evento(termino_de_servico,tempo_atual+gerador->ExponencialInversa(taxa_servico));//Agendar evento de termino de servico
				filaEventos.push(proxTerminoServico);
				cout << "          Inserindo cliente da fila 1 no servidor." << endl;
				cout << "          Agendando proximo termino de servico da fila 1 para " << proxTerminoServico.getTempoAcontecimento() << endl;;
				
			}
			else if(!fila2.empty())
			{
				cliente_em_servico = fila2.front();
				fila2.pop_front();
			
				servidor_vazio = false;
				//Se o cliente, que veio da fila 2, não foi interrompido, gere para ele o seu tempo de serviço
				if(cliente_em_servico.VerificaInterrompido() == N_INTERROMPIDO) 
				{
					Evento proxTerminoServico = Evento(termino_de_servico,tempo_atual+gerador->ExponencialInversa(taxa_servico));//Agenda evento de termino de servico
					filaEventos.push(proxTerminoServico);
					cout << "          Inserindo cliente da fila 2 no servidor." << endl;
					cout << "          Agendando proximo termino de servico da fila 2 para " << proxTerminoServico.getTempoAcontecimento() << endl;
				}

				else 
				{
					Evento proxTerminoServico = Evento(termino_de_servico,tempo_atual+cliente_em_servico.GetTempoRestante());//Agenda evento de termino de servico, com o tempo restante de servico do cliente que foi interrompido
					filaEventos.push(proxTerminoServico);
					cout << "          Inserindo cliente da fila 1 no servidor. Este cliente ja foi interrompido alguma vez." << endl;
					cout << "          Agendando proximo termino de servico da fila 2 para " << proxTerminoServico.getTempoAcontecimento() << endl;
				}
				

			}
		}
	}
	ImprimeResultados(num_total_clientes, tempo_atual);
} 

void Simulador::ImprimeResultados(int n, double t){
     /*
     Divide cada uma das variaveis de fila Nq1, Nq2, N1 e N2 pelo tempo total
     de simulacao para obter a media de cada uma delas, e imprime na tela
     */
         double Nq1 = Nq1_parcial/t;
         double Nq2 = Nq2_parcial/t;
         double N1 = N1_parcial/t;
         double N2 = N2_parcial/t;
         
         cout << endl <<endl << endl << "Imprimindo resultados: "<< endl;
         cout << "     E[Nq1] = " << Nq1 << endl;
         cout << "     E[Nq2] = " << Nq2 << endl;
         cout << "     E[N1] = " << N1 << endl;
         cout << "     E[N2] = " << N2 << endl;
}
            

