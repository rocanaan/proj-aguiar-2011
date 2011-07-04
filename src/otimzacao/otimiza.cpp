#include "..\include\Simulador.h"
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <ctime>
#define CONF95  1.96
#define SEMENTE_INICIAL 175
#define NUM_SEMENTES_TESTE 500
#define NUM_MAXIMO_CLIENTES 30000
#define MAXIMO_IC_ACEITO 4
#define MAXIMO_IC_ACEITO_TESTE 5
#define INCREMENTO_RODADAS 50
#define INCREMENTO_TAMANHO_RODADA 50

using namespace std;

bool VerificaIntervaloConfianca(int num_rodadas, int max_ic, vector<double> E_N1, vector<double> E_N2, vector<double> E_Nq1, vector<double> E_Nq2, vector<double> E_W1, vector<double> E_W2, vector<double> E_T1, vector<double> E_T2, vector<double> V_W1, vector<double> V_W2);
bool TesteIndependenciaSemente(int num_clientes, int num_rodada, double taxa_chegada, int tamanho_transiente);

int main (void)
{
	double taxa_chegada;
	int num_clientes = 20000;
	int num_rodadas = 0;
	int semente = 0;
	int tamanho_transiente;
	bool minimo;
	int rodada_minima;
	long int media_rodadas = 0;
	long int fator_minimo = 0;
	int num_rodada_minima;
	int num_clientes_minimo;
	char time [10];
	ofstream output;


	output.open("FatorMinimo.txt", ios::app);


	cout<<endl<<"Entre com a taxa de chegada que deseja otimizar: ";
	cin>>taxa_chegada;
	cout<<endl<<"Qual o tamanho da fase Transiente? ";
	cin>>tamanho_transiente;

	/*
		Instancia o simulador. Só é necessário uma instância. Em outros pontos do código reiniciamos alguns valores.
	*/
	Simulador simula = Simulador(taxa_chegada,1,0,0,0, semente);

	output<<endl<<"Taxa usada: "<<taxa_chegada<<endl;
	output<<"Tamanho da fase transiente: "<<tamanho_transiente<<endl;
	
	_strtime(time);
	output<<"Tempo de inicio: "<<time<<endl;
	
	while( num_clientes < NUM_MAXIMO_CLIENTES)
	{
		/*
			A semente, para a mesma taxa, nunca será a mesma. 
		*/
		semente+= SEMENTE_INICIAL;
		media_rodadas = 0;
		num_rodadas = 0;
		minimo = false;
		
		cout<<"Tamanho das rodadas:"<< num_clientes<< endl;
		
				/*
					Enquanto não encontramos um fator mínimo o simulador é executado.
					A cada passo incrementamos o número de rodadas.
				*/
				while(!minimo)
				{
					simula.Setup(semente,0);
					
					for( int i = 0 ; i < num_rodadas+1 ; i++)
					{
						if(num_rodadas == 0)
							simula.Roda(tamanho_transiente,num_rodadas, 0, 0, 0, 0, "pasta", 0,0, 0);
						else
							simula.Roda(num_clientes,num_rodadas,  0, 0, 0, 0, "pasta", 0,0, 0);
							
							simula.LimpaResultadosParciais();
					}
					
					/*
						Só a partir de um certo número de rodadas que é interessante verificar os ICs.
						Decidimos que 50 é um valor razoável.
					*/
					if(num_rodadas > 50)
					{
						 minimo = VerificaIntervaloConfianca(num_rodadas,MAXIMO_IC_ACEITO, simula.GetE_N1(),  simula.GetE_N2(),  simula.GetE_Nq1(),  simula.GetE_Nq2(),  simula.GetE_W1(),  simula.GetE_W2(),  simula.GetE_T1(),  simula.GetE_T2(), simula.GetV_W1(),  simula.GetV_W2());
					}
					cout << "rodada:"<<num_rodadas << endl;

					num_rodadas=num_rodadas+INCREMENTO_RODADAS;
				}

				num_rodadas = num_rodadas-INCREMENTO_RODADAS;
				
		

		/*
			Inicialmente o primeiro valor encontrado será sempre o mínimo.
			Mas depois verificamos se o valor anterior é menor do que o atual.
			Se for menor ele se torna o novo fator mínimo.
		*/
		if(fator_minimo == 0)
		{
			fator_minimo = num_clientes*num_rodadas;
			num_clientes_minimo = num_clientes;
			num_rodada_minima = num_rodadas;
			output <<endl<<"Fator minimo atual:"<< fator_minimo<<endl;
			output << "Tamanho rodada minimo atual:"<< num_clientes_minimo<<endl;
			output << "Numero de rodadas minima atual:"<< num_rodada_minima<<endl;
		}
		else if( num_rodadas*num_clientes < fator_minimo)
		{
			_strtime(time);
			output<<"Tempo da escolha: "<<time<<endl;
			fator_minimo = num_rodadas*num_clientes;
			num_clientes_minimo = num_clientes;
			num_rodada_minima = num_rodadas;
			output <<endl<< "Fator minimo atual: "<< fator_minimo<<endl;
			output << "Tamanho rodada minimo atual: "<< num_clientes_minimo<<endl;
			output << "Numero de rodadas minima atual: "<< num_rodada_minima<<endl;
		}
		
		num_clientes+= INCREMENTO_TAMANHO_RODADA;
	}
		_strtime(time);
		output<<"Tempo de Término da escolha: "<<time<<endl;
		
		/*
			O intervalo deve ser aprovado no teste de independencia da semente.
		*/
		if(TesteIndependenciaSemente(num_clientes_minimo,num_rodada_minima,taxa_chegada,tamanho_transiente))
			output<<"O intervalo foi aprovado !! "<<endl;
		else
			output<<"O intervalo NAO foi aprovado "<<endl;
	
		_strtime(time);
		output<<"Tempo de Término do Teste de Semente: "<<time<<endl;
		
		cout<<"************** FIM *****************"<<endl;
		
		system("pause");

	output.close();
	return 0;
}


/*
	Método responsável por verificar se todos os intervalos de confiança estão menores que o valor da variável max_ic ( no nosso caso recebe o valor 4)
*/
bool VerificaIntervaloConfianca(int num_rodadas,int max_ic, vector<double> E_N1, vector<double> E_N2, vector<double> E_Nq1, vector<double> E_Nq2, vector<double> E_W1, vector<double> E_W2, vector<double> E_T1, vector<double> E_T2, vector<double> V_W1, vector<double> V_W2)
{
	double estimador_media, estimador_var, intervalo;

 	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de W1--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)E_W1[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)E_W1[i]) - estimador_media) * (((double)E_W1[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	if(((200.0 * intervalo) / estimador_media) > max_ic)
	{
		return false;
	}

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de T1--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)E_T1[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)E_T1[i]) - estimador_media) * (((double)E_T1[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));
	
	if(((200.0 * intervalo) / estimador_media) > max_ic)
		return false;
	



    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de V_W1--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)V_W1[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)V_W1[i]) - estimador_media) * (((double)V_W1[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	if(((200.0 * intervalo) / estimador_media) > max_ic)
		return false;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de Nq1--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)E_Nq1[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)E_Nq1[i]) - estimador_media) * (((double)E_Nq1[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	if(((200.0 * intervalo) / estimador_media) > max_ic)
		return false;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de N1--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)E_N1[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)E_N1[i]) - estimador_media) * (((double)E_N1[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	if(((200.0 * intervalo) / estimador_media) > max_ic)
		return false;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de W2--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)E_W2[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)E_W2[i]) - estimador_media) * (((double)E_W2[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	if(((200.0 * intervalo) / estimador_media) > max_ic)
		return false;
	

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de T2--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)E_T2[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)E_T2[i]) - estimador_media) * (((double)E_T2[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	if(((200.0 * intervalo) / estimador_media) > max_ic)
		return false;
	

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de V_W2--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)V_W2[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)V_W2[i]) - estimador_media) * (((double)V_W2[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	if(((200.0 * intervalo) / estimador_media) > max_ic)
		return false;

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de Nq2--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)E_Nq2[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)E_Nq2[i]) - estimador_media) * (((double)E_Nq2[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	if(((200.0 * intervalo) / estimador_media) > max_ic)
		return false;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de N2--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)E_N2[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)E_N2[i]) - estimador_media) * (((double)E_N2[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	if(((200.0 * intervalo) / estimador_media) > max_ic)
		return false;

	return true;

}

/*
	Bateria de testes para determinarmos se o mínimo encontrado independe da semente
*/
bool TesteIndependenciaSemente(int num_clientes, int num_rodadas, double taxa_chegada, int tamanho_transiente)
{
	int num_aceitos = 0;
	int max_permitido = NUM_SEMENTES_TESTE - NUM_SEMENTES_TESTE*0.05;
	int semente = 125;
	
	int num =0;

	Simulador simula = Simulador(taxa_chegada,1,0,0,0, semente);
	
	for( int i = 0; i < NUM_SEMENTES_TESTE ; i++)
	{
		semente+= SEMENTE_INICIAL;

		simula.Setup(semente,0);
		for( int i = 0 ; i < num_rodadas+1 ; i++)
		{
			if(num_rodadas == 0)
				simula.Roda(tamanho_transiente,num_rodadas, 0, 0, 0, 0, "pasta", 0,0, 0);
			else
				simula.Roda(num_clientes,num_rodadas,  0, 0, 0, 0, "pasta", 0,0, 0);
				
				simula.LimpaResultadosParciais();
		}
		cout<<num++<<endl;
		
		if(VerificaIntervaloConfianca(num_rodadas,MAXIMO_IC_ACEITO_TESTE, simula.GetE_N1(),  simula.GetE_N2(),  simula.GetE_Nq1(),  simula.GetE_Nq2(),  simula.GetE_W1(),  simula.GetE_W2(),  simula.GetE_T1(),  simula.GetE_T2(), simula.GetV_W1(),  simula.GetV_W2()))
		{
			num_aceitos++;
			cout<<"APROVADO"<<endl;
		}

		
	}
	cout << " Passou " << num_aceitos<< " vezes"<<endl;
	if(num_aceitos >= max_permitido)
		return true;
	else
		return false;

}
