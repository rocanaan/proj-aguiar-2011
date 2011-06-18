class GeradorTaxaExponencial
{
	private:
		unsigned int b;
		unsigned int z0;
		unsigned int c;
		unsigned int m;
		unsigned int zn;
	
	protected:
		
		
	public:
		GeradorTaxaExponencial();
		GeradorTaxaExponencial(unsigned int b, unsigned int z0, unsigned int c, unsigned int m=0xFFFFFFFF); //0xFFFFFFFF = (2^31) - 1
		~GeradorTaxaExponencial();	
	
		bool DefinirSementeAleatoria(); //Faz com que a semente inicial seja dada por um número aleatório dado pela função srand do C
		double Random(); //Função do Gerador de Números Aleatórios
		double ExponencialInversa(double taxa); //Faz a inversa do log para encontrar uma exponencial
};
