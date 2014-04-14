#include "Hash.h"

/*
**
*/
/*
**
*/

Hashish::NoColisao::NoColisao(){}

Hashish::NoColisao::NoColisao(const char* palavra)  /*Inicializar nó de colisão com string de id.*/
{
    Palavra = new char[strlen(palavra)];
    sprintf(Palavra, "%s", palavra);
}

Hashish::NoColisao::~NoColisao()    /*Desalocar string de id.*/
{
    delete [] Palavra;
}

/*
**
*/

void Hashish::Celula::Adicionar(char* palavra, unsigned int arquivo, unsigned long local) /*Verificar se celula com a palavra já */
{                                                                                           /*existe, se não existir, criar colisão.*/
                                                                                            /*Adicionar ocorrência.*/
    NoColisao* p = ListaColisoes.Search(palavra);

    if(p == NULL)
        p = AdicionarColisao(palavra);


    NoArquivo* q = p->ListaArquivos.Search(arquivo);
    if(q = NULL)
        q = AdicionarArquivo(p, arquivo);

    q->ListaOcorrencias.Insert(local);
}

Hashish::NoColisao* Hashish::Celula::AdicionarColisao(char* palavra)
{
    NoColisao* NovoNo = new NoColisao(palavra);
    return ListaColisoes.Insert(NovoNo, palavra);
}

NoArquivo* Hashish::Celula::AdicionarArquivo(NoColisao* Colisao, unsigned int arquivo)
{
    NoArquivo* NovoNo = new NoArquivo;
    NovoNo->Index = arquivo;
    return Colisao->ListaArquivos.Insert(NovoNo, arquivo);
}

/*
void Hashish::Celula::NoColisao::RetornarArquivos(ModulodePesquisa* conteiner)   /*Preencher o conteiner com a lista de textos.
{
    conteiner->num_ocorrencias = 0;
    NoTexto* p = listatexto;

    while(p != NULL)
    {
        conteiner->num_ocorrencias += p->relev;
        p = p->prox;
    }

    conteiner->listatexto = listatexto;
}
*/
/*
**
*/



/*
bool Hashish::Celula::Pesquisa(ModulodePesquisa* conteiner) /*Pesquisar dentro da célula por uma palavra específica.
{                                                           /*Se a palavra for encontrada, incorporar lista de arquivos *
                                                            /*no módulo de pesquisa e retornar true. Se não, false.*
    NoColisao* p = colisoes;

    while(p != NULL)
    {
        if(!strcmp(p->palavra, conteiner->palavra))
        {
            p->RetornarArquivos(conteiner);
            return true;
        }
        p = p->prox;
    }
    return false;
}
*/

/*
**
*/

Hashish::Hashish(unsigned int Tamanho) /*Inicializar o hash, alocando Tamanho células.*/
{
    tamanho = Tamanho;
    tabela = new Celula[tamanho];
}
Hashish::~Hashish() /*Esvaziar a tabela do hash.*/
{
    printf("Deleting hashish table.\n");
    delete [] tabela;
}

unsigned int Hashish::AgregarValor(const char* palavra) /*Definir o hash da palavra.*/
{
    unsigned int retorno = 0;

    for(int c = 0; c < strlen(palavra); c++)
        retorno += palavra[c]*pow(2, c);

    return retorno%tamanho;
}


void Hashish::Adicionar(char* item, unsigned int arquivo, unsigned long local)  /*Adicionar dados às listas internas do hash.*/
{
    tabela[AgregarValor(item)].Adicionar(item, arquivo, local);
}/*
void Hashish::Pesquisa(ModulodePesquisa* conteiner) /*Anular o conteiner caso nenhum resultado for encontrado durante a pesquisa.
{
    if(tabela[AgregarValor(conteiner->Palavra_Chave)].Pesquisa(conteiner))
        return;
    conteiner = NULL;
}
*/

