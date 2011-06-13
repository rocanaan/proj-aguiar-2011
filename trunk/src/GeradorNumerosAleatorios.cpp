#include "..\include\GeradorNumerosAleatorios.h"
#include <iostream>

GeradorNumerosAleatorios* GeradorNumerosAleatorios::instancia = NULL;

GeradorNumerosAleatorios::GeradorNumerosAleatorios()
{
	time_t tempo;

	tempo = time(NULL);

	this->b = 13;
	this->z0 = (int) tempo;
	this->c = 0;
	this->m = 0xFFFFFFFF;

	this->zn = z0;
}

GeradorNumerosAleatorios::GeradorNumerosAleatorios(unsigned int b, unsigned int z0, unsigned int c, unsigned int m)
{
	this->b = b;
	this->z0 = z0;
	this->c = c;
	this->m = m;
	
	this->zn = z0;
}

GeradorNumerosAleatorios* GeradorNumerosAleatorios::GetInstance()
{
	if (instancia == NULL)
		instancia = new GeradorNumerosAleatorios();
	
	return instancia;
}

double GeradorNumerosAleatorios::Random()
{
	zn = (b * zn + c) % m;
	
	return zn / (double) m;
}

/*int GeradorNumerosAleatorios::Random(int b, int z0, int c, int m)
{
	if (instancia == NULL)
		instancia = new GeradorNumerosAleatorios(b, z0, c, m);
	
	zn = (b * zn + c) % m;
	
	return zn;
}*/
