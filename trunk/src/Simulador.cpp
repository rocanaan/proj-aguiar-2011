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

Simulador::Simulador(double ptaxa_chegada, double ptaxa_servico, bool deterministico, bool dois_por_vez, bool interrupcao_forcada, int semente)
{

    /*
		No modo "dois por vez" e de "interrupcao forçada", trabalhamos com
		metade da taxa de chegada fornecida pelo usuario. Assim mantemos a taxa efetiva igual a que foi dada.
	*/
    if(dois_por_vez or interrupcao_forcada)
                     taxa_chegada = ptaxa_chegada/2;
    else
                     taxa_chegada = ptaxa_chegada;
	
    taxa_servico = ptaxa_servico;

                    
	gerador = GeradorTempoExponencial::GetInstancia();
	
	/*
		Se definimos alguma semente, então usar ela no gerador
	*/
	if (semente > 0)
		gerador->DefinirSemente(semente);
		
	/*
		Limpa a heap de eventos, as filas e os dados
	*/
 	while(!filaEventos.empty()) filaEventos.pop();
	while(!fila1.empty()) fila1.pop();
    fila2.clear();
	while(!E_N1.empty()) E_N1.pop_back();
	while(!E_N2.empty()) E_N2.pop_back();
	while(!E_Nq1.empty()) E_Nq1.pop_back();
	while(!E_Nq2.empty()) E_Nq2.pop_back();
	while(!E_W1.empty()) E_W1.pop_back();
	while(!E_W2.empty()) E_W2.pop_back();
	while(!E_T1.empty()) E_T1.pop_back();
	while(!E_T2.empty()) E_T2.pop_back();
	while(!E_T1.empty()) E_T1.pop_back();
	while(!E_T2.empty()) E_T2.pop_back();
	while(!V_W1.empty()) V_W1.pop_back();
	while(!V_W2.empty()) V_W2.pop_back();

	/*
		Coloca o primeiro evendo na "heap" de eventos
	*/
	filaEventos.push(Evento(nova_chegada,gerador->GeraTempoExponencial(taxa_chegada, deterministico)));
	servidor_vazio = true;
	id_proximo_cliente = 0;
	tempo_atual = 0.0;

	total_clientes_servidos_uma_vez =0;
    total_clientes_servidos_duas_vezes = 0;
	acumulaW1 = 0.0;
	acumulaT1 = 0.0;
	acumulaW2 = 0.0;
	acumulaT2 = 0.0;
	acumula_quadradoW1 = 0.0;
	acumula_quadradoW2 = 0.0;

	/*
		Inicia as variaveis que acumulam o (numero de pessoas * tempo) de cada região do sistema
    */
	Nq1_parcial = 0.0;
	Nq2_parcial = 0.0;
	N1_parcial = 0.0;
	N2_parcial = 0.0;


}

Simulador::Simulador()
{
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
void Simulador::Roda(int num_clientes_por_rodada, int rodada_atual, bool debug, bool deterministico, bool determina_transiente, bool dois_por_vez, string nome_pasta, bool guardar_estatisticas, bool interrupcao_forcada, bool mostrar_resultados)
{
    int num_servicos_tipo_1_rodada_atual = 0;
	int num_servicos_tipo_2_rodada_atual = 0;

	double tempo_inicio_rodada = tempo_atual;
	
	if(dois_por_vez)
	{
                    cout << "Rodando em modo dois por vez" << endl;
    }


	//Enquanto o número total de clientes que queremos servir for maior que o número de clientes já servidos por completo, rodamos a simulação
	while(num_clientes_por_rodada > num_servicos_tipo_2_rodada_atual)
	{

		Evento evento_atual = filaEventos.top();//O primeiro evento é selecionado
		filaEventos.pop();//Ele é retirado da Fila
		double tempo_desde_evento_anterior = evento_atual.GetTempoAcontecimento()-tempo_atual;
		tempo_atual=evento_atual.GetTempoAcontecimento();

		if(debug)
		{
			cout << endl << "Evento sendo tratado: Evento do tipo " << evento_atual.GetNome() << " no instante " << tempo_atual << endl;
			cout << "A fila de Eventos tem tamanho " << filaEventos.size() << " apos remover o evento atual" << endl;
			cout << "Status do sistema (antes de resolver o evento):" << endl;
			if(servidor_vazio)
							  cout << "     O servidor esta vazio" << endl;
			else
							  cout << "     O cliente numero " << cliente_em_servico.GetID() << " esta em servico, vindo da fila " << cliente_em_servico.GetFila() <<endl;
			cout << "     Numero de pessoas na fila 1: " << fila1.size()  << endl;
			cout << "     Numero de pessoas na fila 2: " << fila2.size() << endl;
        }



        /////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////COLETA DE DADOS/////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////

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
		if (rodada_atual != 0)
		{
			Nq1_parcial += fila1.size()*tempo_desde_evento_anterior;
			Nq2_parcial += fila2.size()*tempo_desde_evento_anterior;
			if (!servidor_vazio)
			{
			   if (cliente_em_servico.GetFila() == 1)
			   {
				  N1_parcial += (1+fila1.size())*tempo_desde_evento_anterior;
				  N2_parcial += fila2.size()*tempo_desde_evento_anterior;
			   }
			   else
			   {
					N1_parcial += fila1.size()*tempo_desde_evento_anterior;
					N2_parcial += (1+fila2.size())*tempo_desde_evento_anterior;
			   }
			}
			else
			{
				 N1_parcial += fila1.size()*tempo_desde_evento_anterior;
				 N2_parcial += fila2.size()*tempo_desde_evento_anterior;
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////FIM DA COLETA DE DADOS//////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////




		//Se o Evento, que está sendo tratado no momento, for do tipo nova_chegada
		if(evento_atual.GetTipo() == nova_chegada or evento_atual.GetTipo() == chegada_artificial)
		{
			//Condição para tratar a interrupção presente no sistema.
			//Se o servidor estiver ocupado e este cliente for da fila 2 então o cliente que acabou de chegar irá interromper este serviço
			if(!servidor_vazio && cliente_em_servico.GetFila() == FILA_2)
			{    
                Evento evento_destruido = filaEventos.top();        
                if(interrupcao_forcada){
                     evento_destruido = RemoveTerminoServico();
                     if(debug)
				     {
                        cout << "          Evento sendo destruido: : Evento do tipo " << evento_destruido.GetNome() << " marcado para o instante " <<  evento_destruido.GetTempoAcontecimento()<< endl;
                     }
                }
				else{
                     //evento_destruido = filaEventos.top(); //Guardamos o Evento a ser destruido
                     filaEventos.pop();//Remove o Evento de Término de serviço gerado por este cliente da fila 2 ( ele vai sempre ser o top)
                     if(debug)
				     {
                        cout << "          Evento sendo destruido: : Evento do tipo " << evento_destruido.GetTipo() << " marcado para o instante " <<  evento_destruido.GetTempoAcontecimento()<< endl;
                     }
                }

				cliente_em_servico.Interromper();//Marca o cliente como sendo um cliente Interrompido
				cliente_em_servico.SetTempoRestante(evento_destruido.GetTempoAcontecimento() - tempo_atual);//O tempo restante para finalizar seu servico é guardado

				fila2.push_front(cliente_em_servico); //Cliente que foi interrompido volta a ser o primeiro da fila 2.
				servidor_vazio = true; //Deixa o servidor vazio
			}

			Cliente cliente_atual = Cliente(id_proximo_cliente,tempo_atual,FILA_1, rodada_atual); //O novo cliente começa na fila 1

			//Como o servidor já vai estar marcado como vazio se ele estivesse ocupado com algum cliente da fila 2 então só é necessário verificar se ele está vazio
			if(servidor_vazio)
			{
				cliente_atual.SetDiretoAoServidor(true);
			}

			id_proximo_cliente++;

			fila1.push(cliente_atual); //Coloca o novo cliente na fila 1
			
			if(evento_atual.GetTipo() == nova_chegada)
            {
               Evento proxChegada = Evento(nova_chegada,tempo_atual+gerador->GeraTempoExponencial(taxa_chegada, deterministico));//Agenda o Evento para a próxima chegada
			   filaEventos.push(proxChegada);
			    if(debug)
               {
                                   cout << "          Agendando proxima chegada para o instante " << proxChegada.GetTempoAcontecimento() << endl;
               }         
            }
			
			if(debug)
			{
				cout << "          Inserindo o cliente " << cliente_atual.GetID() << " na fila 1" << endl;
			}
			
			if(dois_por_vez and evento_atual.GetTipo() == nova_chegada)
			{
                            Evento artificial = Evento(chegada_artificial,tempo_atual);
			                filaEventos.push(artificial);
                            if(debug)
                            {
                                              cout << "          Agendando chegada artificial para o instante " << artificial.GetTempoAcontecimento() << endl;
                            }                   
            }
            
            if(interrupcao_forcada and evento_atual.GetTipo() == nova_chegada)
            {
             Evento artificial = Evento(chegada_artificial,tempo_atual+gerador->GeraTempoExponencial(taxa_servico*2/3, deterministico));
			 filaEventos.push(artificial);
                             if(debug)
                             {
                                                cout << "          Agendando chegada artificial para o instante " << artificial.GetTempoAcontecimento() << endl;
                             }                   
            }


		}//Se o Evento, que está sendo tratado no momento, for do termino_de_servico
		else if (evento_atual.GetTipo() == termino_de_servico)
		{
			if(cliente_em_servico.GetFila() == FILA_1)
			{
				cliente_em_servico.SetFila(FILA_2);//O cliente que irá terminar o serviço agora é definido como da fila 2
				cliente_em_servico.SetInstanteChegada2(tempo_atual);

				fila2.push_back(cliente_em_servico);// Coloca o cliente na fila 2

				//Se a fila 2 só tem o próprio cliente e não tem ninguem em serviço, quer dizer que o cliente da fila 2 será atendido direto
				if(fila2.size() == 1 && fila1.empty())
					fila2.back().SetDiretoAoServidor(true);
				else
					fila2.back().SetDiretoAoServidor(false);

				if(debug)
				{
					cout << "          Fim de servico na fila 1. Inserindo cliente " << cliente_em_servico.GetID() << " na fila 2" << endl;
				}




				/////////////////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////COLETA DE DADOS/////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				//Verifica se o cliente em serviço é da rodada(coloração usada) em que estamos, pois só esse cliente entra nos dados desta rodada
				if((cliente_em_servico.GetRodadaPertencente() == rodada_atual or determina_transiente) and rodada_atual != 0)
				{
					if(!cliente_em_servico.GetDiretoAoServidor())
						cliente_W1 = cliente_em_servico.W1();
					else
						cliente_W1 = 0;


					acumulaW1 += cliente_W1;
					acumulaT1 += cliente_em_servico.T1();
					acumula_quadradoW1 += cliente_W1*cliente_W1;

					if(debug)
					{
						cout << "          Dados do cliente " << cliente_em_servico.GetID() << ": W1 =  " << cliente_W1 << ", T1 = " << cliente_em_servico.T1() << endl;
					}
					num_servicos_tipo_1_rodada_atual ++;
					total_clientes_servidos_uma_vez ++;
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////FIM DA COLETA DE DADOS//////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////




			}
			else
			{
				//Acabou os 2 serviços do cliente, logo marcamos mais um cliente servido totalmente
				if(debug)
				{
					cout  <<"          Fim de servico na fila 2. Removendo cliente " << cliente_em_servico.GetID() << " do sistema" << endl;
				}
				cliente_em_servico.SetInstanteSaida(tempo_atual);



				/////////////////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////COLETA DE DADOS/////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				//Verifica se o cliente em serviço é da rodada(coloração usada) em que estamos, pois só esse cliente entra nos dados desta rodada
				if((cliente_em_servico.GetRodadaPertencente() == rodada_atual or determina_transiente) and rodada_atual != 0)
				{
					total_clientes_servidos_duas_vezes ++;
					num_servicos_tipo_2_rodada_atual ++;

					if(cliente_em_servico.VerificaInterrompido() == N_INTERROMPIDO && cliente_em_servico.GetDiretoAoServidor())
						cliente_W2 = 0;
					else
						cliente_W2 = cliente_em_servico.W2();

					acumulaW2 += cliente_W2;
					acumulaT2 += cliente_em_servico.T2();
					acumula_quadradoW2 += cliente_W2*cliente_W2;

					if(debug)
					{
						cout << "          Dados do cliente " << cliente_em_servico.GetID() << ": W2 =  " << cliente_W2 << ", T2 = " << cliente_em_servico.T2() << endl;
					}
				}
				
				if(rodada_atual == 0)
					num_servicos_tipo_2_rodada_atual ++;

				/////////////////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////FIM DA COLETA DE DADOS//////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////
	
			}

			//
			servidor_vazio = true;//Como alguem foi servido marcamos o servidor como vazio
		}

		//Se não tem ninguem no servidor
		if(servidor_vazio == true )
		{
			//Fila 1 tem prioridade
			if(!fila1.empty())
			{
				cliente_em_servico = fila1.front();//O primeiro cliente da fila 1 entra em servico
				fila1.pop();//O cliente é removido da fila 1

				servidor_vazio = false;//O servidor agora está ocupado
				double duracao = gerador->GeraTempoExponencial(taxa_servico, deterministico);
				Evento proxTerminoServico = Evento(termino_de_servico,tempo_atual+duracao);//Agendar evento de termino de servico
				filaEventos.push(proxTerminoServico);
				cliente_em_servico.SetDuracaoPrimeiroServico(duracao);

				if(debug)
				{
					cout << "          Transferindo cliente " << cliente_em_servico.GetID() << " da fila 1 para o servidor." << endl;
					cout << "          Agendando termino do primeiro servico do cliente " << cliente_em_servico.GetID() <<" para o instante " << proxTerminoServico.GetTempoAcontecimento() << endl;;
				}
			}
			else if(!fila2.empty())
			{
				cliente_em_servico = fila2.front();
				fila2.pop_front();
				servidor_vazio = false;

				//Se o cliente, que veio da fila 2, não foi interrompido, gere para ele o seu tempo de serviço
				if(cliente_em_servico.VerificaInterrompido() == N_INTERROMPIDO)
				{
					double duracao = gerador->GeraTempoExponencial(taxa_servico,deterministico);
                    Evento proxTerminoServico = Evento(termino_de_servico,tempo_atual+duracao);//Agenda evento de termino de servico
					filaEventos.push(proxTerminoServico);
					cliente_em_servico.SetDuracaoSegundoServico(duracao);

					if(debug)
					{
						cout << "          Transferindo cliente " << cliente_em_servico.GetID() << " da fila 2 para o servidor." << endl;
						cout << "          Agendando termino do segundo servico do cliente " << cliente_em_servico.GetID() << " para o instante " << proxTerminoServico.GetTempoAcontecimento() << endl;
					}
				}

				else
				{
					Evento proxTerminoServico = Evento(termino_de_servico,tempo_atual+cliente_em_servico.GetTempoRestante());//Agenda evento de termino de servico, com o tempo restante de servico do cliente que foi interrompido
					filaEventos.push(proxTerminoServico);
					if(debug)
					{
						cout << "          Inserindo cliente " << cliente_em_servico.GetID() << " da fila 2 no servidor. Este cliente ja foi interrompido alguma vez." << endl;
						cout << "          Agendando termino do segundo servico do cliente " << cliente_em_servico.GetID() << " para " << proxTerminoServico.GetTempoAcontecimento() << endl;
				    }
				}


			}
		}
		if(debug)
                           cout << "A fila de Eventos tem tamanho " << filaEventos.size() << endl;
	}
	if( rodada_atual != 0)
	{
		if(!determina_transiente)
		{
			CalculaResultados(num_servicos_tipo_2_rodada_atual, num_servicos_tipo_1_rodada_atual, tempo_atual - tempo_inicio_rodada, rodada_atual, mostrar_resultados, nome_pasta, guardar_estatisticas);
		}
		else
		{
			CalculaResultados(total_clientes_servidos_duas_vezes, total_clientes_servidos_uma_vez, tempo_atual, rodada_atual, mostrar_resultados, nome_pasta, guardar_estatisticas);
		}
	}

}

void Simulador::CalculaResultados(int n, int servidos1, double t, int rodada, bool mostrar_resultados, string nome_pasta, bool guardar_estatisticas)
{
    /*
    Divide cada uma das variaveis de fila Nq1, Nq2, N1 e N2 pelo tempo da rodada
     para obter a media de cada uma delas
    */
    E_Nq1.push_back(Nq1_parcial/t);
    E_Nq2.push_back(Nq2_parcial/t);
    E_N1.push_back(N1_parcial/t);
    E_N2.push_back(N2_parcial/t);

    /*
    Divide cada um dos acumuladores dos clientes pelo numero de clientes servidos
    */
    double EW1 = acumulaW1/servidos1;
    double ET1 = acumulaT1/servidos1;
    double EW2 = acumulaW2/n;
    double ET2 = acumulaT2/n;
    
    E_W1.push_back(EW1);
    E_T1.push_back(ET1);
    E_W2.push_back(EW2);
    E_T2.push_back(ET2);


     /* O estimador da variância é dado por (1/(n-1)) * somatório de ( ( Xi - Xmédio)^2) para cada amostra i, se forem feitas n amostras
     mas
     somatório de ( ( Xi - Xmédio)^2) para cada amostra i =
     somatório de ( ( Xi^2 - 2Xi*Xmédio + Xmedio^2)) para cada amostra i
     passando o somatório para dentro, temos
     somatório de ( Xi^2) para cada amostra i - 2* somatório de ( Xi*Xmedio) para cada amostra i + somatório de (Xmédio)^2) para cada amostra i
     = acumula_quadradoX - 2*acumulaX*E[X] + n*E[X]^2

     mas E[X] = acumulaX/n, logo -2*acumulaX*E[X] = -2*E(X)^2*n
     e (numero de amostras)*E[X]^2 = acumulaX^2/n

     Assim, V(X) = (acumula_quadradoX - 2*acumulaX^2/n + acumulaX^2/n) * 1/(n-1)
     V(X) = (aumula_quadradoX - acumulaX^2/n) * 1/(n-1)

     para X = W1 ou X = W2
     */

	V_W1.push_back((acumula_quadradoW1 - EW1*EW1*servidos1)/(servidos1-1));
    V_W2.push_back((acumula_quadradoW2 - EW2*EW2*n)/(n-1));
    


    if(mostrar_resultados)
	{
		cout << endl <<endl << endl << "Imprimindo resultados da rodada "<< rodada+1 <<" :"<< endl;
		cout << "     E[W1] = " << E_W1.back() << endl;
		cout << "     E[T1] = " << E_T1.back() << endl;
		cout << "     V[W1] = " << V_W1.back() << endl;
        cout << "     E[Nq1] = " << E_Nq1.back() << endl;
        cout << "     E[N1] = " << E_N1.back() << endl << endl;
        cout << "     E[W2] = " << E_W2.back() << endl;
        cout << "     E[T2] = " << E_T2.back() << endl;
		cout << "     V[W2] = " << V_W2.back() << endl;
		cout << "     E[Nq2] = " << E_Nq2.back() << endl;
		cout << "     E[N2] = " << E_N2.back() << endl;
	}
	
	if(guardar_estatisticas)
		GeraDadosGrafico(rodada, E_N1.back(), E_N2.back(), E_Nq1.back(), E_Nq2.back(), E_W1.back(), E_W2.back(), E_T1.back(), E_T2.back(), V_W1.back(),V_W2.back(), nome_pasta);
}

void Simulador::LimpaResultadosParciais()
{

	acumulaW1 = 0.0;
	acumulaT1 = 0.0;
	acumulaW2 = 0.0;
	acumulaT2 = 0.0;

	Nq1_parcial = 0.0;
	Nq2_parcial = 0.0;
	N1_parcial = 0.0;
	N2_parcial = 0.0;

	acumula_quadradoW1 = 0.0;
	acumula_quadradoW2 = 0.0;

}

void Simulador::GeraDadosGrafico(int rodada, double pN1, double pN2, double pNq1, double pNq2, double pW1, double pW2, double pT1, double pT2, double pV_W1, double pV_W2, string nome_pasta)
{
	ofstream outputFile;
	string temp_pasta = nome_pasta;
	
	nome_pasta.append("/N1.txt");
	char *arquivo = (char*)nome_pasta.c_str();
	outputFile.open(arquivo, ios::app);
	outputFile << rodada <<"\t"<< pN1 << endl;
	outputFile.close();

	nome_pasta = temp_pasta;
	nome_pasta.append("/N2.txt");
	arquivo = (char*)nome_pasta.c_str();
	outputFile.open(arquivo, ios::app);
	outputFile << rodada <<"\t"<< pN2 << endl;
	outputFile.close();

	nome_pasta = temp_pasta;
	nome_pasta.append("/Nq1.txt");
	arquivo = (char*)nome_pasta.c_str();
	outputFile.open(arquivo, ios::app);
	outputFile << rodada <<"\t"<< pNq1 << endl;
	outputFile.close();

	nome_pasta = temp_pasta;
	nome_pasta.append("/Nq2.txt");
	arquivo = (char*)nome_pasta.c_str();
	outputFile.open(arquivo, ios::app);
	outputFile << rodada <<"\t"<< pNq2 << endl;
	outputFile.close();

	nome_pasta = temp_pasta;
	nome_pasta.append("/W1.txt");
	arquivo = (char*)nome_pasta.c_str();
	outputFile.open(arquivo, ios::app);
	outputFile << rodada <<"\t"<< pW1 << endl;
	outputFile.close();

	nome_pasta = temp_pasta;
	nome_pasta.append("/W2.txt");
	arquivo = (char*)nome_pasta.c_str();
	outputFile.open(arquivo, ios::app);
	outputFile << rodada <<"\t"<< pW2 << endl;
	outputFile.close();

	nome_pasta = temp_pasta;
	nome_pasta.append("/T1.txt");
	arquivo = (char*)nome_pasta.c_str();
	outputFile.open(arquivo, ios::app);
	outputFile << rodada <<"\t"<< pT1 << endl;
	outputFile.close();

	nome_pasta = temp_pasta;
	nome_pasta.append("/T2.txt");
	arquivo = (char*)nome_pasta.c_str();
	outputFile.open(arquivo, ios::app);
	outputFile << rodada <<"\t"<< pT2 << endl;
	outputFile.close();

	nome_pasta = temp_pasta;
	nome_pasta.append("/V_W1.txt");
	arquivo = (char*)nome_pasta.c_str();
	outputFile.open(arquivo, ios::app);
	outputFile << rodada <<"\t"<< pV_W1 << endl;
	outputFile.close();

	nome_pasta = temp_pasta;
	nome_pasta.append("/V_W2.txt");
	arquivo = (char*)nome_pasta.c_str();
	outputFile.open(arquivo, ios::app);
	outputFile << rodada <<"\t"<< pV_W2 << endl;
	outputFile.close();
}

Evento Simulador::RemoveTerminoServico(){
     priority_queue<Evento, vector<Evento>, greater<Evento> > filaTemp;
     Evento topo = filaEventos.top();
     while(topo.GetTipo() != termino_de_servico){
        cout << "oi" << endl;
        filaTemp.push(filaEventos.top());
        filaEventos.pop();
        topo = filaEventos.top();
     }
     filaEventos.pop();
     while(!filaTemp.empty()){
        filaEventos.push(filaTemp.top());
        filaTemp.pop();
     }
     return topo;
}
        

vector<double> Simulador::GetE_Nq1()
{
	return E_Nq1;
}
vector<double> Simulador::GetE_Nq2()
{
	return E_Nq2;
}
vector<double> Simulador::GetE_N1()
{
	return E_N1;
}
vector<double> Simulador::GetE_N2()
{
	return E_N2;
}
vector<double> Simulador::GetE_W1()
{
	return E_W1;
}
vector<double> Simulador::GetE_T1()
{
	return E_T1;
}
vector<double> Simulador::GetE_W2()
{
	return E_W2;
}
vector<double> Simulador::GetE_T2()
{
	return E_T2;
}
vector<double> Simulador::GetV_W1()
{
	return V_W1;
}
vector<double> Simulador::GetV_W2()
{
	return V_W2;
}
