//Com amor,
//~zanv.
#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <cmath>
#include <cstring>
#include <cstdio>
#include "List.cpp"

/*
**
**
**
*/

struct ModulodePesquisa;
struct ModuloArquivo;

struct NoArquivo    /*Contem uma lista de todas ocorrencias de uma palavra dentro de determinado arquivo de texto.*/
{
    unsigned int Index;
    NoArquivo(unsigned int);
    NoArquivo();
    VectorList<unsigned long> ListaOcorrencias;
};

struct Palavra
{
    char* str;
    Palavra();
    Palavra(char*);
    ~Palavra();

    bool operator==(Palavra);
};

class Hashish
{
private:

    /* Na busca por ocorrências, primeiro deve-se encontrar a célula no hash, então a palavra na lista de colisões.
    O No palavra possuíra uma sub-lista de textos com ocorrências, e cada NoTexto possuirá uma sub-lista de ocorrências.
    Célula->Palavra->Texto->Lista de ocorrências.*/

    struct NoColisao
    {
        Palavra id;
        List<NoArquivo, unsigned int> ListaArquivos;

        NoColisao(Palavra);
        NoColisao();
        void RetornarArquivos(ModulodePesquisa*);
    };
    struct Celula
    {
        List<NoColisao, Palavra> ListaColisoes;

        void Adicionar(Palavra, unsigned int, unsigned long);
        bool Pesquisa(ModulodePesquisa*);
    };

    Celula* tabela;
    unsigned int tamanho;       /*Definido no construtor, essencial para a função de agregação de valor.*/
    unsigned int AgregarValor(const char*);

public:
    Hashish(unsigned int);
    ~Hashish();
    void Adicionar(char*, unsigned int, unsigned long);
    void Pesquisa(ModulodePesquisa*);
};

struct ModuloArquivo
{
    unsigned int Index;
    unsigned long* Ocorrencias;
    unsigned long Contador;
    bool operator>(ModuloArquivo*);
    bool operator<(ModuloArquivo*);
    ModuloArquivo& operator=(const ModuloArquivo&);
    ~ModuloArquivo();
};
struct ModulodePesquisa /*Tipo base utilizado para obter informações sobre a estrutura do Hash.*/
{
    char* Palavra_Chave;
    unsigned long Contador_Arquivos;
    ModuloArquivo* Arquivos;
    ~ModulodePesquisa();
};


/*
**
**
**
*/

#endif // HASH_H_INCLUDED
