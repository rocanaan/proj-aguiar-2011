#ifndef FUNCOES__H
#define FUNCOES__H

double inversa2(double taxa)
{
	return (-1) * (log(1 - GeradorNumerosAleatorios::GetInstance()->Random()) / taxa);
}
#endif