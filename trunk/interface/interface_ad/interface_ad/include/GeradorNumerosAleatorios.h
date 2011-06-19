#include <stdio.h>
#include <time.h>
#include <iostream>

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

	class Cliente
	{
	private:
		int _id;
		double _tempo_servico;
		int _tipo_servico;
	public:
		Cliente(int novo_id, int taxa);
		inline int id(){return _id;}; 
		inline void tempo_servico(double tempo){_tempo_servico = tempo;};
		inline double tempo_servico(){return _tempo_servico;};
		inline int tipo_servico(){return _tipo_servico;};
		inline void tipo_servico(int servico){_tipo_servico = servico;};
	};
	