//ATEN��O:
//Por estar usando a fun��o srand/rand o valor m�ximo que pode ser sorteado � RAND_MAX = (2^16) - 1

#include "include\GeradorTaxaExponencial.h"
#include <iostream>
#include <math.h>

//Inicializa��o da instancia
GeradorTaxaExponencial* GeradorTaxaExponencial::instancia = NULL;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------Contrutores & Destrutor-----------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GeradorTaxaExponencial::GeradorTaxaExponencial() : CRandomMersenne(0)
{
}

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

//Define uma nova semente para o gerador de n�meros aleat�rios(resetando ele antes)
void GeradorTaxaExponencial::DefinirSemente(int semente)
{
	CRandomMersenne::RandomInit(semente);
}

//Fun��o do Gerador de N�meros Aleat�rios
double GeradorTaxaExponencial::Random()
{
	return CRandomMersenne::Random();
}

/* 
Se o modo deterministico for selecionado, gera a m�dia de uma vari�vel exponencial com a taxa dada = 1/taxa
Caso contr�rio, gera uma amostra de uma distribui��o homog�nea no intervalo de 0 a 1
e aplica a fun��o inversa da CDF da exponencial para gerar uma amostra de vari�vel exponencial.
*/
double GeradorTaxaExponencial::GeraTempoExponencial(double taxa, bool deterministico)
{
    if (deterministico)
       return (1 / taxa);
	return (-1) * (log(1 - this->Random()) / taxa);
}
