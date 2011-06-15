#include "include\Evento.h"
#include <string>

using namespace std;

    Evento::Evento(EnumTipo ptipo, double ptempo_chegada)
	{
        this->tipo = ptipo;
        this->tempo_chegada = ptempo_chegada;
    }
                             
    EnumTipo Evento::getTipo()
	{
        return tipo;
    }
	
    double Evento::getTempoChegada()
	{
        return tempo_chegada;
    }
	
    ostream& Evento::imprime(ostream& o)
	{
        o << "Evento do tipo " << tipo << " marcado para " << tempo_chegada << endl;
    }
