#include "Hash.h"

Hashish::No::No()
{
    prox = NULL;
}

Hashish::Celula::Celula()
{
    colisoes = NULL;
    ultima = colisoes;
    contador = 0;
}
Hashish::Celula::~Celula()
{
    if(colisoes->prox == NULL)
    {
        delete colisoes;
        colisoes = NULL;
    }
    else
    {
        No* proximo_ponteiro;
        proximo_ponteiro = colisoes->prox;

        while(colisoes->prox != NULL)
        {
            delete colisoes;
            colisoes = proximo_ponteiro;
            proximo_ponteiro = colisoes->prox;
        }

        delete colisoes;
        colisoes = NULL;
    }
}
void Hashish::Celula::Adicionar(const char* item)
{
    if(ultima == NULL)
    {
        ultima = new No;
        ultima->palavra = item;
        contador++;
    }
    else
    {
        ultima = ultima->prox;
        ultima = new No;
        ultima->palavra = item;
        contador++;
    }
}
bool Hashish::Celula::Ocorrencias(NoTexto* item, const char* palavra)
{
    No* ponteiro = colisoes;

    while(ponteiro != NULL)
    {
        if(!strcmp(ponteiro->palavra, palavra))
            return true;
        ponteiro = ponteiro->prox;
    }
    return false;
}
Hashish::Hashish(int t)
{
    tamanho = t;
    tabela = new Celula[tamanho];
}
Hashish::~Hashish()
{
    delete [] tabela;
}

int Hashish::AgregarValor(const char* palavra)
{
    int retorno = 0;

    for(int c = 0; c < strlen(palavra); c++)
        retorno += palavra[c]*pow(2, c);

    return retorno%tamanho;
}
void Hashish::Adicionar(const char* item)
{
    tabela[AgregarValor(item)].Adicionar(item);
}
void Hashish::Pesquisa(ModulodePesquisa* item)
{
    tabela[AgregarValor(item->palavra)].Ocorrencias(item->listatexto, item->palavra);
}
