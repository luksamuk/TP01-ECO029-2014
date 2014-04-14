#include "Hash.h"

/*
**
*/
/*
**
*/
NoArquivo::NoArquivo() {}
NoArquivo::NoArquivo(unsigned int index)
{
    Index = index;
}


Hashish::NoColisao::NoColisao() {}

Hashish::NoColisao::NoColisao(Palavra palavra)  /*Inicializar nó de colisão com string de id.*/
{
    id = palavra;
}

/*
**
*/

void Hashish::Celula::Adicionar(Palavra chave, unsigned int arquivo, unsigned long local) /*Verificar se celula com a palavra já */
{
    /*existe, se não existir, criar colisão.*/
    /*Adicionar ocorrência.*/
    NoColisao *p;
    NoArquivo *q;
    p = ListaColisoes.Search(chave);

    #ifdef DEBUG
    printf("Searching for '%s' cell collision -> %p\n", chave.str, p);
    printf("Cell contains %d collisions.\n", ListaColisoes.Length());
    #endif
    if(p == NULL)
    {
        NoColisao* NovoNo = new NoColisao(chave);
        p = ListaColisoes.Insert(*NovoNo, chave);
        #ifdef DEBUG
        printf("New collision in %p.\n", p);
        #endif
    }
    else
    {
        #ifdef DEBUG
        printf("Collision in %p.\n", p);
        #endif
    }


    q = p->ListaArquivos.Search(arquivo);
    #ifdef DEBUG
    printf("Looking for file index %d -> %p.\n", arquivo, q);
    printf("File list of size %d.\n", p->ListaArquivos.Length());
    #endif
    if(q == NULL)
    {
        NoArquivo* NovoNo = new NoArquivo(arquivo);
        q = p->ListaArquivos.Insert(*NovoNo, local);
        #ifdef DEBUG
        printf("New file index at %p.\n", q);
        #endif
    }
    else{
    #ifdef DEBUG
    printf("File index found in %p.\n", q);
    #endif
    }

    q->ListaOcorrencias.Insert(local);
    #ifdef DEBUG
    printf("Inserting new word location at %d in file %d.\n", local, arquivo);
    #endif
}


void Hashish::NoColisao::RetornarArquivos(ModulodePesquisa* conteiner)   /*Preencher o conteiner com a lista de textos.*/
{

    conteiner->Arquivos = new ModuloArquivo[ListaArquivos.Length()];    //Se a palavra foi encontrada, é certo que Length é > 0.
    conteiner->Contador_Arquivos = ListaArquivos.Length();
    NoArquivo* arq = ListaArquivos.DataVector(NULL);

    for(int c = 0; c < conteiner->Contador_Arquivos; c++)
    {
        conteiner->Arquivos[c].Index = arq[c].Index;
        conteiner->Arquivos[c].Ocorrencias = arq[c].ListaOcorrencias.DataVector(&conteiner->Arquivos[c].Contador);
    }
}

/*
**
*/

bool Hashish::Celula::Pesquisa(ModulodePesquisa* conteiner) /*Pesquisar dentro da célula por uma palavra específica.*/
{
    /*Se a palavra for encontrada, incorporar lista de arquivos *
    /*no módulo de pesquisa e retornar true. Se não, false.*/
    NoColisao* p = ListaColisoes.Search(conteiner->Palavra_Chave);

    if(p)
    {
        p->RetornarArquivos(conteiner);
        return true;
    }
    return false;
}


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
    #ifdef DEBUG
    printf("Deleting hashish's cell table.\n");
    #endif
    delete [] tabela;
}

unsigned int Hashish::AgregarValor(const char* palavra) /*Definir o hash da palavra.*/
{
    unsigned int retorno = 0;

    for(int c = 0; c < strlen(palavra); c++)
        retorno += palavra[c]*pow(2, c);
    #ifdef DEBUG
    printf("\nValue aggregated to word %s -> %d.\n", palavra, retorno%tamanho);
    #endif
    return retorno%tamanho;
}


void Hashish::Adicionar(char* item, unsigned int arquivo, unsigned long local)  /*Adicionar dados às listas internas do hash.*/
{
    Palavra chave(item);
    tabela[AgregarValor(item)].Adicionar(chave, arquivo, local);
}
void Hashish::Pesquisa(ModulodePesquisa* conteiner) /*Anular o conteiner caso nenhum resultado for encontrado durante a pesquisa.*/
{
    if(tabela[AgregarValor(conteiner->Palavra_Chave)].Pesquisa(conteiner))
        return;
    conteiner = NULL;
}


bool ModuloArquivo::operator<(ModuloArquivo* b)
{
    if(Contador < b->Contador)
        return true;
    return false;
}
bool ModuloArquivo::operator>(ModuloArquivo* b)
{
    if(Contador > b->Contador)
        return true;
    return false;
}

Palavra::Palavra() {}
Palavra::Palavra(char* palavra)
{
    str = new char[strlen(palavra)];
    sprintf(str, "%s", palavra);
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

