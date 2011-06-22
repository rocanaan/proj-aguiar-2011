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
	while (repeat != "N" and repeat !="n")
    {     
	      Simulador s = Simulador(0.3,1);
	      s.Roda(10);
    
          cout << "Deseja fazer uma nova simulacao? (S/N)" << endl;
          getline(cin,repeat);
    }
	
	return 0;
}
