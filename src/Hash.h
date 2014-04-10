//Com amor,
//~zanv.

#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include <cmath>
#include <cstring>


struct NoOcorrencia
{
    NoOcorrencia* prox;
    int linha;  //Posição da palavra nesta ocorrência. Pode não ser necessariamente a linha.
};
struct NoTexto
{
    NoTexto* prox;
    const char* arquivo;
    int relev;    /*Relevância, deve ser incrementada a cada adição de ocorrência.
                  Será usada como chave, pode ser usada para ordenar a lista de 'NoTexto's*/
    NoOcorrencia* listaocor;    //Ponteiro para o começo da sub-lista contendo as ocorrências da palavra neste texto.
};

struct ModulodePesquisa
{
    const char* palavra;
    int num_ocorrencias;
    NoTexto* listatexto;
};

class Hashish
{
private:

    /* Na busca por ocorrências, primeiro deve-se encontrar a célula no hash, então a palavra na lista de colisões.
    O No palavra possuíra uma sub-lista de textos com ocorrências, e cada NoTexto possuirá uma sub-lista de ocorrências.
    Célula->Palavra->Texto->Lista de ocorrências */

    struct No
    {
        No* prox;
        const char* palavra;
        No();

        NoTexto* listatexto; //Ponteiro para o começo da sub-lista de textos nos quais a palavra aparece
    };
    struct Celula
    {
        No* colisoes;
        No* ultima;
        int contador;

        Celula();
        ~Celula();
        void Adicionar(const char*);
        bool Ocorrencias(NoTexto* textos, const char*); //Função que retorna a lista de textos contendo a lista de ocorrencias.
    };

    Celula* tabela;
    int tamanho;
    int AgregarValor(const char*);

public:
    Hashish(int);
    ~Hashish();
    void Adicionar(const char*);
    void Pesquisa(ModulodePesquisa*);   //Precisa de um ModulodePesquisa previamente instanciado.
};



#endif // HASH_H_INCLUDED
