//ATENÇÃO:
//Por estar usando a função srand/rand o valor máximo que pode ser sorteado é RAND_MAX = (2^16) - 1
#include "Mersenne/randomc.h"

class GeradorTaxaExponencial : CRandomMersenne
{
	private:
		static GeradorTaxaExponencial *instancia;
	
	protected:
		GeradorTaxaExponencial();
		~GeradorTaxaExponencial();	
	
	public:
		static GeradorTaxaExponencial* GetInstancia(); //Retorna a instancia única do gerador de números aleatórios
	
		void DefinirSemente(int semente); //Muda a semente do gerador de números aleatórios(resetando ele anteriormente)
		double Random(); //Função do Gerador de Números Aleatórios
		double ExponencialInversa(double taxa); //Faz a inversa do log para encontrar uma exponencial
};
