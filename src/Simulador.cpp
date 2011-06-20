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
	
	acumulaW1=0;
	acumulaT1=0;
	acumulaW2=0;
	acumulaT2=0;
	
	/*
    inicia as variaveis que acumulam o (numero de pessoas * tempo) de cada regi�o do sistema
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
//------------------------------------------Fun��es Membro-------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Fun��o principal do simulador, executa a simula��o
void Simulador::Roda(int num_total_clientes)   
{
	int num_clientes_servidos = 0;
	int num_clientes_servidos_uma_vez =0;
	
	//Enquanto o n�mero total de clientes que queremos servir for maior que o n�mero de clientes j� servidos por completo, rodamos a simula��o
	while(num_total_clientes > num_clientes_servidos)
	{
	
		Evento evento_atual = filaEventos.top();//O primeiro evento � selecionado 
		filaEventos.pop();//Ele � retirado da Fila
		double tempo_desde_evento_anterior = evento_atual.getTempoAcontecimento()-tempo_atual;
		tempo_atual=evento_atual.getTempoAcontecimento();
		cout << "Evento sendo tratado: Evento do tipo " << evento_atual.getTipo() << " no tempo " << tempo_atual << endl;
		cout << "Status do sistema (antes de resolver o evento):" << endl;
		if(servidor_vazio)
		                  cout << "     O servidor esta vazio" << endl;
		else
		                  cout << "     Existe 1 cliente em servico, vindo da fila " << cliente_em_servico.GetFila() <<endl;
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
 
		//Se o Evento, que est� sendo tratado no momento, for do tipo nova_chegada
		if(evento_atual.getTipo() == nova_chegada)
		{
			//Condi��o para tratar a interrup��o presente no sistema.
			//Se o servidor estiver ocupado e este cliente for da fila 2 ent�o o cliente que acabou de chegar ir� interromper este servi�o
			if(!servidor_vazio && cliente_em_servico.GetFila() == FILA_2)
			{
				Evento evento_destruido = filaEventos.top(); //Guardamos o Evento a ser destruido
				filaEventos.pop();//Remove o Evento de T�rmino de servi�o gerado por este cliente da fila 2 ( ele vai sempre ser o top)
				cout << "          Evento sendo destruido: : Evento do tipo " << evento_destruido.getTipo() << " marcado para " <<  evento_destruido.getTempoAcontecimento()<< endl;
				
				cliente_em_servico.FoiInterrompido();//Marca o cliente como sendo um cliente Interrompido
				cliente_em_servico.SetTempoRestante(evento_destruido.getTempoAcontecimento() - tempo_atual);//O tempo restante para finalizar seu servico � guardado
				
				fila2.push_front(cliente_em_servico); //Cliente que foi interrompido volta a ser o primeiro da fila 2.
				servidor_vazio = true; //Deixa o servidor vazio
			}
			
			Cliente cliente_atual = Cliente(id_proximo_cliente,tempo_atual,FILA_1); //O novo cliente come�a na fila 1
			
			//Como o servidor j� vai estar marcado como vazio se ele estivesse ocupado com algum cliente da fila 2 ent�o s� � necess�rio verificar se ele est� vazio
			if(servidor_vazio)
			{
				cliente_atual.SetDiretoAoServidor(true);
				cout << "Cliente foi direto ao servidor"<<endl;
			}
			
			id_proximo_cliente++; 
			
			fila1.push(cliente_atual); //Coloca o novo cliente na fila 1
			
			Evento proxChegada = Evento(nova_chegada,tempo_atual+gerador->ExponencialInversa(taxa_chegada));//Agenda o Evento para a pr�xima chegada
			filaEventos.push(proxChegada);
			cout << "          Inserindo o cliente " << cliente_atual.getID() << " na fila 1" << endl;
			cout << "          Agendando nova chegada para " << proxChegada.getTempoAcontecimento() << endl;
			
		}//Se o Evento, que est� sendo tratado no momento, for do termino_de_servico
		else if (evento_atual.getTipo() == termino_de_servico)
		{
			if(cliente_em_servico.GetFila() == FILA_1)
			{
				cliente_em_servico.SetFila(FILA_2);//O cliente que ir� terminar o servi�o agora � definido como da fila 2
				cliente_em_servico.setInstanteChegada2(tempo_atual);
				
				fila2.push_back(cliente_em_servico);// Coloca o cliente na fila 2
				
				//Se a fila 2 s� tem o pr�prio cliente e n�o tem ninguem em servi�o, quer dizer que o cliente da fila 2 ser� atendido direto
				if(fila2.size() == 1 && servidor_vazio)
					fila2.front().SetDiretoAoServidor(true);

				cout << "          Fim de servico na fila 1. Inserindo cliente " << cliente_em_servico.getID() << " na fila 2" << endl;
				/*
                coleto as estatisticas do cliente aqui ou quando ele sai do servidor?
                depende, tenho que ver com o Aguiar
                vou fazer como se fosse aqui
                */
				if(!cliente_em_servico.GetDiretoAoServidor())
					cliente_W1 = cliente_em_servico.W1();
				else
					cliente_W1 = 0;
					
				cliente_em_servico.SetDiretoAoServidor(false);
				
				acumulaW1 += cliente_W1;
                acumulaT1 += cliente_em_servico.T1();
                cout << "          Dados do cliente " << cliente_em_servico.getID() << ": W1 =  " << cliente_W1 << ", T1 = " << cliente_em_servico.T1() << endl;
                // OBS: Problema quando o cliente nao passou pela fila. W1 nao sai = 0 por erro de precis�o.
                num_clientes_servidos_uma_vez ++;
			}
			else
			{
				//Acabou os 2 servi�os do cliente, logo marcamos mais um cliente servido totalmente
				cout  <<"          Fim de servico na fila 2. Removendo cliente " << cliente_em_servico.getID() << " do sistema" << endl;
				num_clientes_servidos++;
				cliente_em_servico.setInstanteSaida(tempo_atual);
				
				if(cliente_em_servico.VerificaInterrompido() == N_INTERROMPIDO && cliente_em_servico.GetDiretoAoServidor())
					cliente_W2 = 0;
				else
					cliente_W2 = cliente_em_servico.W2();
				
				acumulaW2 += cliente_W2;
				acumulaT2 += cliente_em_servico.T2();
				cout << "          Dados do cliente " << cliente_em_servico.getID() << ": W2 =  " << cliente_W2 << ", T2 = " << cliente_em_servico.T2() << endl;
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
				double duracao = gerador->ExponencialInversa(taxa_servico);
				Evento proxTerminoServico = Evento(termino_de_servico,tempo_atual+duracao);//Agendar evento de termino de servico
				filaEventos.push(proxTerminoServico);
				cliente_em_servico.setDuracaoPrimeiroServico(duracao);
				cout << "          Transferindo cliente " << cliente_em_servico.getID() << " da fila 1 para o servidor." << endl;
				cout << "          Agendando termino do primeiro servico do cliente " << cliente_em_servico.getID() <<" para " << proxTerminoServico.getTempoAcontecimento() << endl;;
				
			}
			else if(!fila2.empty())
			{
				cliente_em_servico = fila2.front();
				fila2.pop_front();
				servidor_vazio = false;
				//Se o cliente, que veio da fila 2, n�o foi interrompido, gere para ele o seu tempo de servi�o
				if(cliente_em_servico.VerificaInterrompido() == N_INTERROMPIDO) 
				{
					double duracao = gerador->ExponencialInversa(taxa_servico);
                    Evento proxTerminoServico = Evento(termino_de_servico,tempo_atual+duracao);//Agenda evento de termino de servico
					filaEventos.push(proxTerminoServico);
					cliente_em_servico.setDuracaoSegundoServico(duracao);
					cout << "          Transferindo cliente " << cliente_em_servico.getID() << " da fila 2 para o servidor." << endl;
					cout << "          Agendando termino do segundo servico do cliente " << cliente_em_servico.getID() << " para " << proxTerminoServico.getTempoAcontecimento() << endl;
				}

				else 
				{
					Evento proxTerminoServico = Evento(termino_de_servico,tempo_atual+cliente_em_servico.GetTempoRestante());//Agenda evento de termino de servico, com o tempo restante de servico do cliente que foi interrompido
					filaEventos.push(proxTerminoServico);
					cout << "          Inserindo cliente " << cliente_em_servico.getID() << " da fila 2 no servidor. Este cliente ja foi interrompido alguma vez." << endl;
					cout << "          Agendando termino do segundo servico do cliente " << cliente_em_servico.getID() << " para " << proxTerminoServico.getTempoAcontecimento() << endl;
				}
				

			}
		}
	}
	ImprimeResultados(num_total_clientes, num_clientes_servidos_uma_vez, tempo_atual);
} 

void Simulador::ImprimeResultados(int n, int servidos1, double t){
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
         
     /*
     Divide cada um dos acumuladores dos clientes pelo numero de clientes servidos
     Falta variancia
     Falta saber se os da fila um s�o tratados apenas quando saem do sistema ou quando s�o servidos pela primeira vez
     */
     double W1 = acumulaW1/servidos1;
     double T1 = acumulaT1/servidos1;
     double W2 = acumulaW2/n;
     double T2 = acumulaT2/n;
     
     cout << endl << "     E[W1] = " << W1 << endl;
     cout << "     E[T1] = " << T1 << endl;
     cout << "     E[W2] = " << W2 << endl;
     cout << "     E[T2] = " << T2 << endl;
     
     
}
            

