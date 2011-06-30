#include <string>
#include <typeinfo>
#include <iostream>
#include <sstream>

const int ERROR = -1;

using namespace std;

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
        inline void num(Tipo valor) { _num = valor; };
        inline string nome() { return _nome; };
		inline bool erro() { return _erro; };
        inline void nome(string valor) { _nome = valor; };
        Tipo num();
        bool procurar_e_adicionar(const string &str);
        bool verificar_valor();
};

template<class Tipo>
Config<Tipo>::Config(string nome_valor)
{
    _nome = nome_valor;
    modificado = false;
	_erro = false;
}

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
