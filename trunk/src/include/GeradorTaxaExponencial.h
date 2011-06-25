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
		
		/* 
       Se o modo deterministico for selecionado, gera a m�dia de uma vari�vel exponencial com a taxa dada = 1/taxa
       Caso contr�rio, gera uma amostra de uma distribui��o homog�nea no intervalo de 0 a 1
       e aplica a fun��o inversa da CDF da exponencial para gerar uma amostra de vari�vel exponencial.
       */
		double GeraTempoExponencial(double taxa, bool deterministico); 
};
