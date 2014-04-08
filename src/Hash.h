//Com amor,
//~zanv.

#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <math.h>
#include <string.h>


class Hashish
{
private:
    struct No
    {
        No* prox;
        const char* palavra;
        No();
    };
    struct Celula
    {
        No* colisoes;
        No* ultima;
        int contador;

        Celula();
        ~Celula();
        void Adicionar(const char*);
        bool Ocorrencias(const char*);//função que retorna lista de ocorrencias
    };

    Celula* tabela;
    int tamanho;
    int AgregarValor(const char*);

public:
    Hashish(int);
    ~Hashish();
    void Adicionar(const char*);
    void Pesquisa(const char*); //deve retornar lista de instancias
};



#endif // HASH_H_INCLUDED
