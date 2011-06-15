#include "include\GeradorNumerosAleatorios.h"
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
	
	for (int i=0; i<60; i++)
		cout << inversa(0.5) << endl;
		//cout << gna->Random() << endl;
	
	return 0;
}
