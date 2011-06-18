#include "include\GeradorTaxaExponencial.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------Contrutores & Destrutor-----------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GeradorTaxaExponencial::GeradorTaxaExponencial()
{
	time_t tempo;

	tempo = time(NULL); //Usado para gerar uma semente inicial a partir do tempo

	this->b = 13;
	this->z0 = (int) tempo;
	this->c = 0;
	this->m = 0xFFFFFFFF;

	this->zn = z0;
}

GeradorTaxaExponencial::GeradorTaxaExponencial(unsigned int b, unsigned int z0, unsigned int c, unsigned int m)
{
	this->b = b;
	this->z0 = z0;
	this->c = c;
	this->m = m;
	
	this->zn = z0;
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

//Faz com que a semente inicial seja dada por um número aleatório dado pela função srand do C
bool GeradorTaxaExponencial::DefinirSementeAleatoria()
{
	if (z0 != zn)
		return false; //Para não permitir que se mude a semente após já ter gerado algum número

	srand(time(NULL));
	z0 = rand() % m;
	zn = z0;
	
	return true;
}

//Função do Gerador de Números Aleatórios
double GeradorTaxaExponencial::Random()
{
	zn = (b * zn + c) % m;
	
	return zn / (double) m; //divido por m para ficar no intervalo [0, 1)
}

//Faz a inversa do log para encontrar uma exponencial
double GeradorTaxaExponencial::ExponencialInversa(double taxa)
{
	return (-1) * (log(1 - this->Random()) / taxa);
}
