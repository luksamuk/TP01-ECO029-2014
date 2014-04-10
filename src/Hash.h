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
            void AdicionarArquivo(const char*, unsigned int);
            void RetornarArquivos(ModulodePesquisa*);
        };

        NoColisao* colisoes;    /*Ponteiro para lista de colisões contidas na célula.*/
        int contador;           /*Incrementado a cada nova colisão.*/

        Celula();
        ~Celula();
        void AdicionarOcorrencia(const char*, const char*, unsigned int);
        bool Pesquisa(ModulodePesquisa*);
    };

    Celula* tabela; /*Ponteiro base.*/
    unsigned int tamanho;    /*Definido no construtor, essencial para a função de agregação de valor.*/
    unsigned int AgregarValor(const char*);

public:
    Hashish(int);
    ~Hashish();
    void Adicionar(const char*, const char*, unsigned int);
    void Pesquisa(ModulodePesquisa*);

};

struct NoTexto
{
    NoTexto* prox;
    char* arquivo;      /*Identificador.*/
    unsigned int relev; /*Relevância, deve ser incrementada a cada adição de ocorrência.
                            Será usada como chave, pode ser usada para ordenar a lista de 'NoTexto's*/

    NoOcorrencia* listaocor;    /*Ponteiro para o começo da sub-lista contendo as ocorrências da palavra neste texto.*/
    NoOcorrencia* ultimaocor;   /*Ponteiro auxiliar para operações de inserção.*/

    NoTexto(const char*);
    ~NoTexto();
    void AdicionarLocal(unsigned int);
};

struct NoOcorrencia
{
    NoOcorrencia* prox;
    unsigned int local; /*Posição da palavra nesta ocorrência.*/
};


struct ModulodePesquisa /*Tipo base utilizado para obter informações sobre a estrutura do Hash.*/
{                       /*Não possui destrutor pois somente aponta para os dados dentro do Hash sem copiá-los.*/
    const char* palavra;
    int num_ocorrencias;
    NoTexto* listatexto;
};


/*
**
**
**
*/

#endif // HASH_H_INCLUDED
