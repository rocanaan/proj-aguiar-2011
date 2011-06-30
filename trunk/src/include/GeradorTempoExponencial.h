#include "Mersenne/randomc.h"

class GeradorTempoExponencial : CRandomMersenne
{
	private:
		static GeradorTempoExponencial *instancia;
	
	protected:
		GeradorTempoExponencial();
		~GeradorTempoExponencial();	
	
	public:
		static GeradorTempoExponencial* GetInstancia(); //Retorna a instancia única do gerador de números aleatórios
	
		void DefinirSemente(int semente); //Muda a semente do gerador de números aleatórios(resetando ele anteriormente)
		double Random(); //Função do Gerador de Números Aleatórios
		
		/* 
       Se o modo deterministico for selecionado, gera a média de uma variável exponencial com a taxa dada = 1/taxa
       Caso contrário, gera uma amostra de uma distribuição homogênea no intervalo de 0 a 1
       e aplica a função inversa da CDF da exponencial para gerar uma amostra de variável exponencial.
       */
		double GeraTempoExponencial(double taxa, bool deterministico); 
};
