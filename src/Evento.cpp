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
/*
	M�todo usado para podermos imprimir o nome dos eventos na tela, no modo debug.
*/
string Evento::GetNome()
{
       if (tipo == 0)
          return "Nova Chegada";
       if (tipo == 1)
          return "Chegada Artificial";
       return "Termino de Servico";
}
          
