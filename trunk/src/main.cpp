#include "include\Simulador.h"
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <typeinfo>
#ifdef WIN32 || _WIN32
    #include <direct.h>
    #define MKDIR(a) _mkdir(a)
#else
     #include <sys/stat.h>
     #define MKDIR(a) mkdir(a, 0777)  /*Aqui o 0777 define o modo como igual ao umask, ou seja as permissões que resultariam de um mkdir na shell */
#endif
#define CONF95  1.96

const int ERROR = -1;
using namespace std;

using namespace std;

void CalculaIntervaloConfianca(int num_rodadas, vector<double> E_N1, vector<double> E_N2, vector<double> E_Nq1, vector<double> E_Nq2, vector<double> E_W1, vector<double> E_W2, vector<double> E_T1, vector<double> E_T2, vector<double> V_W1, vector<double> V_W2);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------Classes utilizadas para o carregamento dos valores ----------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Tipo>
class Config
{
    private:
        Tipo _num;
        string _nome;
        bool modificado;
		bool _erro;
    public:
        Config(string nome_valor);
        inline void num(Tipo valor){_num = valor;};
        inline string nome(){return _nome;};
		inline bool erro(){return _erro;};
        inline void nome(string valor){_nome = valor;};
        Tipo num();
        bool procurar_e_adicionar(const string &str);
        bool verificar_valor();
};
template<class Tipo>
Tipo Config<Tipo>::num()
{
    string compara = typeid(Tipo).name();
    if (!modificado && compara.compare("b"))
        return ERROR;
    else
        return _num;
}
template<class Tipo>
Config<Tipo>::Config(string nome_valor)
{
    _nome = nome_valor;
    modificado = false;
	_erro = false;
}
template<class Tipo>
bool Config<Tipo>::procurar_e_adicionar(const string &str)
{
    size_t pos, fim;
    Tipo temp;
    istringstream str_number;
    string valor;

    pos = str.find(_nome);
    if (pos != string::npos)
    {

        pos = str.find("=",pos) + 1;
        fim = str.find(";",pos);
        for (int i = pos;i < fim;i++)
        {

            if (str.compare(i,1," ") != 0)
                valor += str.substr(i,1);
        }
        if (valor.compare("true") && valor.compare("false"))
        {
            str_number.str(valor);
            str_number >> _num;
        }
        else
        {
            if (!valor.compare("true"))
                _num = true;
            else
                _num = false;
        }
        modificado = true;
        return true;
    }
    return false;
}
template<class Tipo>
bool Config<Tipo>::verificar_valor()
{
    if (!modificado)
    {
        string compara = typeid(Tipo).name();
        if (!compara.compare("b"))
            _num = false;
        else
        {
            cout<<"Faltando variavel ' " << _nome << " ' no arquivo de configuracao."<<endl;
			_erro = true;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------FIM das classes pro carregamento ----------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(void)
{
	
	bool repeat = true;
	char repeat_temp;
	/*
	int num_rodadas ;
	double taxa_chegada ;
	int num_clientes ;
	bool deterministico ;
	bool debug;
	bool determina_transiente;
	bool dois_por_vez;
	*/
	
	Config<int> *num_rodadas = new Config<int>("num_rodadas");
    Config<int> *num_clientes = new Config<int>("num_clientes");
    Config<double> *taxa_chegada = new Config<double>("taxa_chegada");
    Config<bool> *deterministico = new Config<bool>("deterministico");
    Config<bool> *debug = new Config<bool>("debug");
    Config<bool> *determina_transiente = new Config<bool>("determina_transiente");
	Config<bool> *dois_por_vez = new Config<bool>("dois_por_vez");
	Config<bool> *guardar_estatisticas = new Config<bool>("guardar_estatisticas");
	
	string nome_arquivo,valor,buffer,nome_pasta;
    ifstream entrada;
    size_t pos, fim,temp;
	
	while (repeat)
    {
		while (1)
		{
			cout<<"Entre com o nome do arquivo que contem as entradas: ";
			cin>>nome_arquivo;
			entrada.clear();
			entrada.open(nome_arquivo.c_str(), ifstream::in);
			if (!entrada.fail())
				break;
			else
			{
				cout<<"Erro abrindo arquivo(O nome do arquivo esta correto?)"<<endl;

			}

		}
		
		while(std::getline(entrada, buffer))
		{
			num_rodadas->procurar_e_adicionar(buffer);
			num_clientes->procurar_e_adicionar(buffer);
			taxa_chegada->procurar_e_adicionar(buffer);
			deterministico->procurar_e_adicionar(buffer);
			debug->procurar_e_adicionar(buffer);
			determina_transiente->procurar_e_adicionar(buffer);
			dois_por_vez->procurar_e_adicionar(buffer);
			guardar_estatisticas->procurar_e_adicionar(buffer);

		}
		
		num_rodadas->verificar_valor();
		num_clientes->verificar_valor();
		taxa_chegada->verificar_valor();
		deterministico->verificar_valor();
		debug->verificar_valor();
		determina_transiente->verificar_valor();
		dois_por_vez->verificar_valor();
		guardar_estatisticas->verificar_valor();
		
		if( !num_rodadas->erro() and  !num_clientes->erro() and !taxa_chegada->erro())
		{
			cout<< endl << num_rodadas->nome()<< ": "<<num_rodadas->num()<<endl;
			cout<<num_clientes->nome()<< ": "<<num_clientes->num()<<endl;
			cout<<taxa_chegada->nome()<< ": "<<taxa_chegada->num()<<endl;
			cout<<deterministico->nome()<< ": "<<deterministico->num()<<endl;
			cout<<debug->nome()<< ": "<<debug->num()<<endl;
			cout<<determina_transiente->nome()<< ": "<<determina_transiente->num()<<endl;
			cout<<dois_por_vez->nome()<< ": "<<dois_por_vez->num()<<endl;
			cout<<guardar_estatisticas->nome()<< ": "<<guardar_estatisticas->num()<<endl;

			cout << endl << "Os valores estao corretos? (S/N)" << endl;
			cin >> repeat_temp;
			if(repeat_temp == 'S' or repeat_temp == 's')
				 repeat = false;
			else 
			{
				entrada.close();
				 repeat = true;
				 
			}
		}
		else
		{
			entrada.close();
		}
    }
	if(guardar_estatisticas->num())
	{
		nome_pasta = nome_arquivo.erase(nome_arquivo.size()-3,3);
		MKDIR(nome_pasta.c_str());
	}
	
	
	
	Simulador simula = Simulador(taxa_chegada->num(),1,deterministico->num(), dois_por_vez->num());

	for( int i = 0 ; i < num_rodadas->num() ; i++)
	{
		simula.Roda(num_clientes->num(),i, debug->num(), deterministico->num(), determina_transiente->num(), dois_por_vez->num(), nome_pasta, guardar_estatisticas);
		if(!determina_transiente->num())
			simula.LimpaResultadosParciais();
	}

    CalculaIntervaloConfianca(num_rodadas->num(), simula.GetE_N1(),  simula.GetE_N2(),  simula.GetE_Nq1(),  simula.GetE_Nq2(),  simula.GetE_W1(),  simula.GetE_W2(),  simula.GetE_T1(),  simula.GetE_T2(), simula.GetV_W1(),  simula.GetV_W2());
	entrada.close();
	
	system("pause");
	return 0;
}

void CalculaIntervaloConfianca(int num_rodadas, vector<double> E_N1, vector<double> E_N2, vector<double> E_Nq1, vector<double> E_Nq2, vector<double> E_W1, vector<double> E_W2, vector<double> E_T1, vector<double> E_T2, vector<double> V_W1, vector<double> V_W2)
{
	double estimador_media, estimador_var, intervalo;

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de N1--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)E_N1[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)E_N1[i]) - estimador_media) * (((double)E_N1[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	printf("E[N1]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);


		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de N2--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)E_N2[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)E_N2[i]) - estimador_media) * (((double)E_N2[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	printf("E[N2]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de Nq1--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)E_Nq1[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)E_Nq1[i]) - estimador_media) * (((double)E_Nq1[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	printf("E[Nq1]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de Nq2--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)E_Nq2[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)E_Nq2[i]) - estimador_media) * (((double)E_Nq2[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	printf("E[Nq2]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);
	
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de W1--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)E_W1[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)E_W1[i]) - estimador_media) * (((double)E_W1[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	printf("E[W1]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de W2--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)E_W2[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)E_W2[i]) - estimador_media) * (((double)E_W2[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	printf("E[W2]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de T1--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)E_T1[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)E_T1[i]) - estimador_media) * (((double)E_T1[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	printf("E[T1]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de T2--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)E_T2[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)E_T2[i]) - estimador_media) * (((double)E_T2[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	printf("E[T2]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de V_W1--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)V_W1[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)V_W1[i]) - estimador_media) * (((double)V_W1[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	printf("V(W1)\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////--------------Cálculo do Intervalo de V_W2--------------////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	estimador_media = 0.0;
	estimador_var = 0.0;
	
    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_media += (double)V_W2[i];
    }
    estimador_media /= (double)num_rodadas;

    for(unsigned int i = 0; i < num_rodadas ; i++)
    {
        estimador_var += (((double)V_W2[i]) - estimador_media) * (((double)V_W2[i]) - estimador_media);
    }
    estimador_var /= (double)(num_rodadas - 1);

    intervalo = CONF95 * (sqrt(estimador_var) / sqrt(num_rodadas));

	printf("V(W2)\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo);
	printf("     Intervalo = %lf ate %lf\n",(estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo);
	printf("     Media do Intervalo: %lf \n", estimador_media);
	printf("     Tamanho: %lf \n",  2.0 * intervalo);
	printf("     Tamanho em relacao a Media: %lf%% \n", (200.0 * intervalo) / estimador_media);

}