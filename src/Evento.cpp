#include "include\Simulador.h"
#include <iostream>
#include <cstdlib>
#include <string>


    Evento::Evento(EnumTipo ptipo, double ptempo_acontecimento)
	{
        this->tipo = ptipo;
        this->tempo_acontecimento = ptempo_acontecimento;
    }

    EnumTipo Evento::getTipo()
	{
        return tipo;
    }
	
    double Evento::getTempoAcontecimento() const
	{
        return tempo_acontecimento;
    }
	
    ostream& Evento::imprime(ostream& o)
	{
        o << "Evento do tipo " << tipo << " marcado para " << tempo_acontecimento << endl;
    }

