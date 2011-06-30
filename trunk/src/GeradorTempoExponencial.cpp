#include "include\GeradorTempoExponencial.h"
#include <iostream>
#include <math.h>
#include <time.h>

//Inicializa��o da instancia
GeradorTempoExponencial* GeradorTempoExponencial::instancia = NULL;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------Contrutores & Destrutor-----------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GeradorTempoExponencial::GeradorTempoExponencial() : CRandomMersenne(0)
{
	int semente = (int) time(0); //Gera uma semente aleat�ria
	
	this->DefinirSemente(semente); //Define a semente do gerador como a semente aleat�ria gerada acima
}

GeradorTempoExponencial::~GeradorTempoExponencial()
{
	//Destrutor
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------Fun��es Membro-------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Retorna a instancia �nica do gerador de n�meros aleat�rios
GeradorTempoExponencial* GeradorTempoExponencial::GetInstancia()
{
	if (instancia == NULL)
		instancia = new GeradorTempoExponencial();
		
	return instancia;
}

//Define uma nova semente para o gerador de n�meros aleat�rios(resetando ele antes)
void GeradorTempoExponencial::DefinirSemente(int semente)
{
	CRandomMersenne::RandomInit(semente);
}

//Fun��o do Gerador de N�meros Aleat�rios
double GeradorTempoExponencial::Random()
{
	return CRandomMersenne::Random();
}

/* 
Se o modo deterministico for selecionado, gera a m�dia de uma vari�vel exponencial com a taxa dada = 1/taxa
Caso contr�rio, gera uma amostra de uma distribui��o homog�nea no intervalo de 0 a 1
e aplica a fun��o inversa da CDF da exponencial para gerar uma amostra de vari�vel exponencial.
*/
double GeradorTempoExponencial::GeraTempoExponencial(double taxa, bool deterministico)
{
    if (deterministico)
       return (1 / taxa);
	return (-1) * (log(1 - this->Random()) / taxa);
}
