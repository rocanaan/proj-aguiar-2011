#ifndef EVENTO_H_
#define EVENTO_H_

#include <stdio.h>
#include <cstdlib>
#include <iostream>

using namespace std;
enum EnumTipo{nova_chegada,termino_de_servico};

class Evento{
	private:
		EnumTipo tipo;
		double tempo_acontecimento;
  
	public:
		Evento(EnumTipo ptipo, double ptempo_acontecimento);
		EnumTipo GetTipo();
		double GetTempoAcontecimento() const;
		inline bool operator > (const Evento evento2) const { return (this->GetTempoAcontecimento() > evento2.GetTempoAcontecimento()); }
};

#endif /*EVENTO_H_*/
      
