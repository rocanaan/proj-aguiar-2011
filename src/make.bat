g++ -c include/mersenne/mersenne.cpp
g++ -c GeradorTempoExponencial.cpp
g++ -c Cliente.cpp
g++ -c Evento.cpp
g++ -c Simulador.cpp
g++ -c include/Config.h
g++ mersenne.o GeradorTempoExponencial.o Cliente.o Evento.o Simulador.o -o main main.cpp
pause

