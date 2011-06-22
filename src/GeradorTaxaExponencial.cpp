//ATEN��O:
//Por estar usando a fun��o srand/rand o valor m�ximo que pode ser sorteado � RAND_MAX = (2^16) - 1

#include "include\GeradorTaxaExponencial.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//Inicializa��o da instancia
GeradorTaxaExponencial* GeradorTaxaExponencial::instancia = NULL;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------Contrutores & Destrutor-----------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GeradorTaxaExponencial::GeradorTaxaExponencial()
{
	srand(time(NULL));
}

/*GeradorTaxaExponencial::GeradorTaxaExponencial(unsigned int semente_inicial)
{
	srand(semente_inicial);
}*/

GeradorTaxaExponencial::~GeradorTaxaExponencial()
{
	//Destrutor
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------Fun��es Membro-------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Retorna a instancia �nica do gerador de n�meros aleat�rios
GeradorTaxaExponencial* GeradorTaxaExponencial::GetInstancia()
{
	if (instancia == NULL)
		instancia = new GeradorTaxaExponencial();
		
	return instancia;
}

//Reseta o gerador de n�meros aleat�rios para poder ser usado com outra semente
void GeradorTaxaExponencial::ResetarGerador()
{
	srand(1); //Passando 1 como argumento, a fun��o srand reinicia, como se nunca tivesse havido uma chamada a srand ou a rand.
}

//Define uma nova semente para o gerador de n�meros aleat�rios(resetando ele antes)
void GeradorTaxaExponencial::DefinirSemente(unsigned int semente)
{
	ResetarGerador();
	srand(semente);
}

//Fun��o do Gerador de N�meros Aleat�rios
double GeradorTaxaExponencial::Random()
{
	return (rand() % RAND_MAX) / (double) RAND_MAX;
}

//Faz a inversa do log para encontrar uma exponencial
double GeradorTaxaExponencial::ExponencialInversa(double taxa)
{
	return (-1) * (log(1 - this->Random()) / taxa);
}
