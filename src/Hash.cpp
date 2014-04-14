#include "Hash.h"

/*
**
*/
/*
**
*/
NoArquivo::NoArquivo(){}
NoArquivo::NoArquivo(unsigned int index)
{
    Index = index;
}


Hashish::NoColisao::NoColisao(){}

Hashish::NoColisao::NoColisao(Palavra palavra)  /*Inicializar nó de colisão com string de id.*/
{
    id = palavra;
}

/*
**
*/

void Hashish::Celula::Adicionar(Palavra chave, unsigned int arquivo, unsigned long local) /*Verificar se celula com a palavra já */
{                                                                                           /*existe, se não existir, criar colisão.*/
                                                                                            /*Adicionar ocorrência.*/

    p = ListaColisoes.Search(chave);

    printf("Celula contem %d colisoes\n", ListaColisoes.Length());
        printf("STRING = %s\n", chave.str);
    printf("Procurando por colisão da palavra %s -> %p\n", chave.str, p);
    if(p == NULL)
    {
        NoColisao* NovoNo = new NoColisao(chave);
        p = ListaColisoes.Insert(*NovoNo, chave);
    }

    printf("Colisão em %p\n", p);
    q = p->ListaArquivos.Search(arquivo);
    printf("Tamanho lista de arquivos %d.\n", p->ListaArquivos.Length());
    printf("Procurando por arquivo com index %d -> %p\n", arquivo, q);
    if(q == NULL)
    {
        NoArquivo* NovoNo = new NoArquivo(arquivo);
        printf("Novo No em %p.\n", NovoNo);
        q = p->ListaArquivos.Insert(*NovoNo, local);
    }

    printf("Arquivo em %p\n", q);
    q->ListaOcorrencias.Insert(local);
    printf("Inserindo ocorrencia %d no arquivo\n", local);
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
    Palavra chave(item);
    tabela[AgregarValor(item)].Adicionar(chave, arquivo, local);
}/*
void Hashish::Pesquisa(ModulodePesquisa* conteiner) /*Anular o conteiner caso nenhum resultado for encontrado durante a pesquisa.
{
    if(tabela[AgregarValor(conteiner->Palavra_Chave)].Pesquisa(conteiner))
        return;
    conteiner = NULL;
}
*/

bool ModuloArquivo::operator<(ModuloArquivo* b){return true;}
bool ModuloArquivo::operator>(ModuloArquivo* b){return true;}

Palavra::Palavra(){}
Palavra::Palavra(char* palavra)
{
    str = new char[strlen(palavra)];
    sprintf(str, "%s", palavra);
    printf("Construtor Palavra str = %s\n", str);
}
Palavra::~Palavra()
{
    //delete str;
}

bool Palavra::operator==(Palavra p)
{
    if(!strcmp(str, p.str))
        return true;
    return false;
}

