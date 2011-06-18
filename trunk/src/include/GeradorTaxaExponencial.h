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
	
		bool DefinirSementeAleatoria(); //Faz com que a semente inicial seja dada por um n�mero aleat�rio dado pela fun��o srand do C
		double Random(); //Fun��o do Gerador de N�meros Aleat�rios
		double ExponencialInversa(double taxa); //Faz a inversa do log para encontrar uma exponencial
};
