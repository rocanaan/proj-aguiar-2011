#include "include\Simulador.h"
#include <iostream>
#include <math.h>

using namespace std;

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
	string temp;
	
	while (repeat != "N" and repeat !="n")
    {
	
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
			simula.Roda(num_clientes,i, debug, deterministico);
			simula.LimpaResultadosParciais();
		}
    
		cout << "Deseja fazer uma nova simulacao? (S/N)" << endl;
		getline(cin,repeat);
    }
	
	return 0;
}
