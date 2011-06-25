#include "include\Evento.h"
#include <iostream>
#include <cstdlib>
#include <string>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------Contrutores ----------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Evento::Evento(EnumTipo ptipo, double ptempo_acontecimento)
{
	this->tipo = ptipo;
	this->tempo_acontecimento = ptempo_acontecimento;
}
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------Fun��es Membro-------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EnumTipo Evento::GetTipo()
{
	return tipo;
}

double Evento::GetTempoAcontecimento() const
{
	return tempo_acontecimento;
}

ostream& Evento::Imprime(ostream& o)
{
	o << "Evento do tipo " << tipo << " marcado para " << tempo_acontecimento << endl;
}