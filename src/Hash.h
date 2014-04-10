//Com amor,
//~zanv.

#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include <cmath>
#include <cstring>
#include <cstdio>

/*
**
**
**
*/

struct ModulodePesquisa;
struct NoTexto;
struct NoOcorrencia;


class Hashish
{
private:

    /* Na busca por ocorrências, primeiro deve-se encontrar a célula no hash, então a palavra na lista de colisões.
    O No palavra possuíra uma sub-lista de textos com ocorrências, e cada NoTexto possuirá uma sub-lista de ocorrências.
    Célula->Palavra->Texto->Lista de ocorrências.*/

    struct Celula
    {
        struct NoColisao
        {
            NoColisao* prox;
            char* palavra;          /*Identificador.*/
            NoTexto* listatexto;    /*Ponteiro para o começo da sub-lista de textos nos quais a palavra aparece.*/

            NoColisao(const char*);
            ~NoColisao();
            void AdicionarArquivo(unsigned int, unsigned long);
            void RetornarArquivos(ModulodePesquisa*);
        };

        NoColisao* colisoes;    /*Ponteiro para lista de colisões contidas na célula.*/
        unsigned long contador;           /*Incrementado a cada nova colisão.*/

        Celula();
        ~Celula();
        void AdicionarOcorrencia(char*, unsigned int, unsigned long);
        bool Pesquisa(ModulodePesquisa*);
    };

    Celula* tabela; /*Ponteiro base.*/
    unsigned int tamanho;    /*Definido no construtor, essencial para a função de agregação de valor.*/
    unsigned int AgregarValor(const char*);

public:
    Hashish(unsigned int);
    ~Hashish();
    void Adicionar(char*, unsigned int, unsigned long);
    void Pesquisa(ModulodePesquisa*);

};

struct NoTexto
{
    NoTexto* prox;
    unsigned int arquivo;      /*Identificador.*/
    unsigned long relev; /*Relevância, deve ser incrementada a cada adição de ocorrência.
                            Será usada como chave, pode ser usada para ordenar a lista de 'NoTexto's*/

    NoOcorrencia* listaocor;    /*Ponteiro para o começo da sub-lista contendo as ocorrências da palavra neste texto.*/
    NoOcorrencia* ultimaocor;   /*Ponteiro auxiliar para operações de inserção.*/

    NoTexto(unsigned int);
    ~NoTexto();
    void AdicionarLocal(unsigned long);
};

struct NoOcorrencia
{
    NoOcorrencia* prox;
    unsigned long local; /*Posição da palavra nesta ocorrência.*/
};


struct ModulodePesquisa /*Tipo base utilizado para obter informações sobre a estrutura do Hash.*/
{                       /*Não possui destrutor pois somente aponta para os dados dentro do Hash sem copiá-los.*/
    const char* palavra;
    unsigned long num_ocorrencias;
    NoTexto* listatexto;
};


/*
**
**
**
*/

#endif // HASH_H_INCLUDED
