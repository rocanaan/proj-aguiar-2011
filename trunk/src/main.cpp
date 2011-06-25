#include "include\Simulador.h"
#include <iostream>
#include <math.h>
#define CONF95  1.96

using namespace std;

void CalculaIntervaloConfianca(int num_rodadas, vector<double> E_N1, vector<double> E_N2, vector<double> E_Nq1, vector<double> E_Nq2, vector<double> E_W1, vector<double> E_W2, vector<double> E_T1, vector<double> E_T2, vector<double> V_W1, vector<double> V_W2);

int main(void)
{
	/*GeradorTaxaExponencial *gna = GeradorTaxaExponencial::GetInstancia();
	
	gna->DefinirSemente(100);
	
	for (int i=0; i<60; i++)
		cout << gna->Random() << endl;*/
	
	string repeat = "";
	int num_rodadas ;
	double taxa_chegada ;
	int num_clientes ;
	bool deterministico ;
	bool debug;
	bool determina_transiente;
	string temp;
	
	while (repeat != "N" and repeat !="n")
    {
        cout << "Deseja rodar o modo de estimacao da fase transiente? (S/N)" << endl;
        getline(cin,temp);
        if(temp == "S" or temp == "s")
	         determina_transiente = true;
        else 
             determina_transiente = false;
        
	
		cout << "Qual a taxa de chegada desejada ?" << endl;
		cin >> taxa_chegada;
		cin.ignore();
		
		cout << "Quantos clientes serao servidos ?" << endl;
		cin >> num_clientes;
		cin.ignore();
		
		cout << "Quantas rodadas ?" << endl;
	    cin >> num_rodadas;
	    cin.ignore();
	    
	    cout << "Deseja rodar em modo deterministico? (S/N)" << endl;
	    getline(cin,temp);
	    if(temp == "S" or temp == "s")
	         deterministico = true;
        else 
             deterministico = false;
             
        cout << "Deseja rodar em modo debug? (S/N)" << endl;
        getline(cin,temp);
        if(temp == "S" or temp == "s")
	         debug = true;
        else 
             debug = false;
        

		Simulador simula = Simulador(taxa_chegada,1,deterministico);

		for( int i = 0 ; i < num_rodadas ; i++)
		{
			simula.Roda(num_clientes,i, debug, deterministico, determina_transiente);
			if(!determina_transiente)
               simula.LimpaResultadosParciais();
		}
    
        CalculaIntervaloConfianca(num_rodadas, simula.GetE_N1(),  simula.GetE_N2(),  simula.GetE_Nq1(),  simula.GetE_Nq2(),  simula.GetE_W1(),  simula.GetE_W2(),  simula.GetE_T1(),  simula.GetE_T2(), simula.GetV_W1(),  simula.GetV_W2());
    
		cout << "Deseja fazer uma nova simulacao? (S/N)" << endl;
		getline(cin,repeat);
    }
	
	return 0;
}

void CalculaIntervaloConfianca(int num_rodadas, vector<double> E_N1, vector<double> E_N2, vector<double> E_Nq1, vector<double> E_Nq2, vector<double> E_W1, vector<double> E_W2, vector<double> E_T1, vector<double> E_T2, vector<double> V_W1, vector<double> V_W2)
{
	double estimador_media, estimador_var, intervalo;

	
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

	printf("E[N1]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);


		
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

	printf("E[N2]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);

	
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

	printf("E[Nq1]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);
	
	
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

	printf("E[Nq2]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);
	
	
	
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

	printf("E[W1]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);
	
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

	printf("E[W2]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);
	
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

	printf("E[T1]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);
	
	
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

	printf("E[T2]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);
	
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

	printf("V(W1)\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);
	
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

	printf("V(W2)\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);
	

	

}
