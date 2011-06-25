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
	int num_rodada ;
	double taxa_chegada ;
	int num_clientes ;
	
	while (repeat != "N" and repeat !="n")
    {
	
		printf("Qual a taxa de chegada desejada ?\n");
		scanf("%lf",&taxa_chegada);
		printf("Quantos clientes serao servidos ?\n");
		scanf("%d",&num_clientes);
		printf("Quantas rodadas ?\n");
		scanf("%d",&num_rodada);

		Simulador simula = Simulador(taxa_chegada,1);

		for( int i = 0 ; i < num_rodada ; i++)
		{
			simula.Roda(num_clientes,i, false);
			simula.LimpaResultadosParciais();
		}
    
		printf("Deseja fazer uma nova simulacao? (S/N)");
		scanf("%s",&repeat);
		printf("\n");
    }
	
	return 0;
}
