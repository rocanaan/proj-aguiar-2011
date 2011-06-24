#include "include\Cliente.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------Contrutores ----------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Cliente::Cliente()
{
	this->id = 0;
	this->fila = 0;
	this->interrompido = 0;
}

Cliente::Cliente(int pid,double instante_chegada, int pfila, int rodada_atual)
{
	this->id = pid;
	this->fila = pfila;
	this->interrompido = false;
	this->instante_chegada1 = instante_chegada;
	this->direto_ao_servidor = false;
	this->rodada_pertencente = rodada_atual;
}
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------Funções Membro-------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Cliente::GetFila()
{
	return fila;
}

int Cliente::SetFila(int pfila)
{
	this->fila = pfila;
}

double Cliente::GetTempoRestante()
{
	return tempo_restante;
}

double Cliente::SetTempoRestante(double ptempo_restante)
{
	this->tempo_restante = ptempo_restante;
}

bool Cliente::VerificaInterrompido()
{
	return interrompido;
}

void Cliente::Interromper()
{
	this->interrompido = true;
}

void Cliente::SetInstanteChegada2(double t)
{
	 this->instante_chegada2=t;
}

void Cliente::SetDuracaoPrimeiroServico(double duracao)
{
	 this->duracao_primeiro_servico=duracao;
}

void Cliente::SetDuracaoSegundoServico(double duracao)
{
	 this->duracao_segundo_servico=duracao;
}

void Cliente::SetInstanteSaida(double t)
{
	 this->instante_saida=t;
}

int Cliente::GetID()
{
	return id;
}

void Cliente::SetDiretoAoServidor(bool pbool)
{
	this->direto_ao_servidor = pbool;
}

bool Cliente::GetDiretoAoServidor()
{
	return direto_ao_servidor;
}

int Cliente::GetRodadaPertencente()
{
	return rodada_pertencente;
}

double Cliente::W1()
{
	   return instante_chegada2 - instante_chegada1 - duracao_primeiro_servico;
}

double Cliente::T1()
{
	   return instante_chegada2 - instante_chegada1;
}

double Cliente::W2()
{
	   return instante_saida - instante_chegada2 - duracao_segundo_servico;
}

double Cliente::T2()
{
	   return instante_saida - instante_chegada2;
}
