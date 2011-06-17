#include "include\Cliente.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

	Cliente::Cliente()
	{
		this->id = 0;
		this->fila = 0;
	}
	
    Cliente::Cliente(int pid,int pfila)
	{
        this->id = pid;
        this->fila = pfila;
    }
	
	int Cliente::GetFila()
	{
		return fila;
	}
	
	int Cliente::SetFila(int pfila)
	{
		this->fila = pfila;
	}