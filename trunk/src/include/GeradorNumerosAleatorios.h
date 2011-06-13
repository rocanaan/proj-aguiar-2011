#include <stdio.h>
#include <time.h>

class GeradorNumerosAleatorios
{
	private:
		static GeradorNumerosAleatorios *instancia;
	
		unsigned int b;
		unsigned int z0;
		unsigned int c;
		unsigned int m;
		unsigned int zn;
	
	protected:
		GeradorNumerosAleatorios();
		GeradorNumerosAleatorios(unsigned int b, unsigned int z0, unsigned int c, unsigned int m=0xFFFFFFFF); //0xFFFFFFFF = (2^31) - 1
		~GeradorNumerosAleatorios();
	
	public:
		static GeradorNumerosAleatorios* GetInstance();
		double Random();
		//int Random(int b, int z0, int c, int m=0xFFFFFFFF);
};
