g++ -c include/mersenne/mersenne.cpp
g++ -c GeradorTaxaExponencial.cpp
g++ -c Cliente.cpp
g++ -c Evento.cpp
g++ -c Simulador.cpp
g++ mersenne.o GeradorTaxaExponencial.o Cliente.o Evento.o Simulador.o -o main main.cpp
pause

