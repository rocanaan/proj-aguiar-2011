#include "include\GeradorTaxaExponencial.h"
#include <iostream>
#include <math.h>
#include <time.h>

//Inicialização da instancia
GeradorTaxaExponencial* GeradorTaxaExponencial::instancia = NULL;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------Contrutores & Destrutor-----------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GeradorTaxaExponencial::GeradorTaxaExponencial() : CRandomMersenne(0)
{
	int semente = (int) time(0); //Gera uma semente aleatória
	
	this->DefinirSemente(semente); //Define a semente do gerador como a semente aleatória gerada acima
}

GeradorTaxaExponencial::~GeradorTaxaExponencial()
{
	//Destrutor
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------Funções Membro-------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Retorna a instancia única do gerador de números aleatórios
GeradorTaxaExponencial* GeradorTaxaExponencial::GetInstancia()
{
	if (instancia == NULL)
		instancia = new GeradorTaxaExponencial();
		
	return instancia;
}

//Define uma nova semente para o gerador de números aleatórios(resetando ele antes)
void GeradorTaxaExponencial::DefinirSemente(int semente)
{
	CRandomMersenne::RandomInit(semente);
}

//Função do Gerador de Números Aleatórios
double GeradorTaxaExponencial::Random()
{
	return CRandomMersenne::Random();
}

/* 
Se o modo deterministico for selecionado, gera a média de uma variável exponencial com a taxa dada = 1/taxa
Caso contrário, gera uma amostra de uma distribuição homogênea no intervalo de 0 a 1
e aplica a função inversa da CDF da exponencial para gerar uma amostra de variável exponencial.
*/
double GeradorTaxaExponencial::GeraTempoExponencial(double taxa, bool deterministico)
{
    if (deterministico)
       return (1 / taxa);
	return (-1) * (log(1 - this->Random()) / taxa);
}
