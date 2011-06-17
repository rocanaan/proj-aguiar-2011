#include "include\GeradorNumerosAleatorios.h"
#include "include\Simulador.h"
#include <iostream>
#include <math.h>

using namespace std;

double inversa(double taxa)
{
	return (-1) * (log(1 - GeradorNumerosAleatorios::GetInstance()->Random()) / taxa);
}

int main(void)
{
	//GeradorNumerosAleatorios *gna = GeradorNumerosAleatorios::GetInstance();
	string repeat = "";
	while (repeat != "N" and repeat !="n")
    {
	      /*for (int i=0; i<60; i++)
		      cout << inversa(0.5) << endl;
		      //cout << gna->Random() << endl;*/
		      
	      Simulador s = Simulador(1,1);
	      s.Roda(10);
    
          cout << "Deseja fazer uma nova simulacao? (S/N)" << endl;
          getline(cin,repeat);
    }
	
	
	return 0;
}
