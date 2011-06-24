//ATEN��O:
//Por estar usando a fun��o srand/rand o valor m�ximo que pode ser sorteado � RAND_MAX = (2^16) - 1
#include "Mersenne/randomc.h"

class GeradorTaxaExponencial : CRandomMersenne
{
	private:
		static GeradorTaxaExponencial *instancia;
	
	protected:
		GeradorTaxaExponencial();
		~GeradorTaxaExponencial();	
	
	public:
		static GeradorTaxaExponencial* GetInstancia(); //Retorna a instancia �nica do gerador de n�meros aleat�rios
	
		void DefinirSemente(int semente); //Muda a semente do gerador de n�meros aleat�rios(resetando ele anteriormente)
		double Random(); //Fun��o do Gerador de N�meros Aleat�rios
		double ExponencialInversa(double taxa); //Faz a inversa do log para encontrar uma exponencial
};
