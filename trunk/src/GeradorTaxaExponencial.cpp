//ATENÇÃO:
//Por estar usando a função srand/rand o valor máximo que pode ser sorteado é RAND_MAX = (2^16) - 1

#include "include\GeradorTaxaExponencial.h"
#include <iostream>
#include <math.h>

//Inicialização da instancia
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

//Faz a inversa do log para encontrar uma exponencial
double GeradorTaxaExponencial::ExponencialInversa(double taxa)
{
	return (-1) * (log(1 - this->Random()) / taxa);
}
