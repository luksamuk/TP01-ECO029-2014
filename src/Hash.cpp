#include "Hash.h"

/*
*/

NoTexto::NoTexto(unsigned int Arquivo)      /*Inicializar a lista de ocorrências e assumir um valor de identificação */
{                                           /*através da variável Arquivo.*/
    printf("Listaocor = NULL;\n");
    listaocor = NULL;
    printf("Ultimaocor = listaocor;\n");
    ultimaocor = listaocor;
    printf("prox = NULL;\n");
    prox = NULL;
    relev = 0;
    arquivo = Arquivo;
}
NoTexto::~NoTexto() /*Deletar os ponteiros da lista de ocorrências.*/
{
    if(listaocor)
    {
        if(listaocor->prox == NULL)
        {
            delete listaocor;
            listaocor = NULL;
        }
        else
        {
            NoOcorrencia* proximo_ponteiro;
            proximo_ponteiro = listaocor->prox;

            while(listaocor->prox != NULL)
            {
                delete listaocor;
                listaocor = proximo_ponteiro;
                proximo_ponteiro = listaocor->prox;
            }

            delete listaocor;
            listaocor = NULL;
        }
    }
}
void NoTexto::AdicionarLocal(unsigned long localizacao)  /*Adiciona mais um local à lista de ocorrencias.*/
{
    printf("Adicionando nova ocorrencia no texto.\n");
    if(ultimaocor == NULL)
    {
        printf("Adicionando primeira ocorrencia.\n");
        ultimaocor = new NoOcorrencia;
        ultimaocor->prox = NULL;
        ultimaocor->local = localizacao;
    }
    else
    {
        printf("Adicionando ultima ocorrencia.\n");
        ultimaocor->prox = new NoOcorrencia;
        ultimaocor = ultimaocor->prox;
        ultimaocor->prox = NULL;
        ultimaocor->local = localizacao;
    }
    relev++;
}

/*
**
*/

Hashish::Celula::NoColisao::NoColisao(const char* Palavra)  /*Inicializar nó de colisão com string de id, */
{                                                            /*e também a lista de arquivos.*/
    prox = NULL;
    listatexto = NULL;
    sprintf(palavra, "%s", Palavra);
}
Hashish::Celula::NoColisao::~NoColisao()    /*Esvaziar ponteiros da lista de textos.*/
{
    if(listatexto)
    {
        if(listatexto->prox == NULL)
        {
            delete listatexto;
            listatexto = NULL;
        }
        else
        {
            NoTexto* proximo_ponteiro;
            proximo_ponteiro = listatexto->prox;

            while(listatexto->prox != NULL)
            {
                delete listatexto;
                listatexto = proximo_ponteiro;
                proximo_ponteiro = listatexto->prox;
            }

            delete listatexto;
            listatexto = NULL;
        }
    }
}

void Hashish::Celula::NoColisao::AdicionarArquivo(unsigned int arquivo, unsigned long local)/*Verificar se arquivo já existe.*/
{                                                                                   /*Se sim, adicionar ocorrência nele.*/
                                                                                    /*Se não, criar outro nó para esse arquivo.*/
                                                                                    /*Adicionar ocorrência.*/
    if(listatexto == NULL)
    {
        printf("Criando indexador de arquivos.\n");
        printf("Arquivo %o.\n");
        //listatexto = new NoTexto(arquivo);
        printf("Lista de textos.\n");
        //listatexto->AdicionarLocal(local);
        printf("Indexador de arquivos criado.\n");
        return;
    }

    NoTexto* p = listatexto;

    while(true)
    {
        if(p->prox == NULL)
            break;

        if(p->arquivo == arquivo)
            break;

        p = p->prox;
    }

    if(p->prox == NULL)
    {
        printf("Inserindo novos arquivos no indexador.\n");
        p->prox = new NoTexto(arquivo);
        p = p->prox;
        p->AdicionarLocal(local);
    }
    else
        p->AdicionarLocal(local);

}
void Hashish::Celula::NoColisao::RetornarArquivos(ModulodePesquisa* conteiner)   /*Preencher o conteiner com a lista de textos.*/
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

/*
**
*/

Hashish::Celula::Celula()   /*Inicializar a lista de colisões e o contador.*/
{
    colisoes = NULL;
    contador = 0;
}
Hashish::Celula::~Celula()  /*Desalocar a lista de colisões da célula.*/
{
    if(colisoes)
    {
        if(colisoes->prox == NULL)
        {
            delete colisoes;
            colisoes = NULL;
        }
        else
        {
            NoColisao* proximo_ponteiro;
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
}
void Hashish::Celula::AdicionarOcorrencia(char* palavra, unsigned int arquivo, unsigned long local)/*Verificar se existem */
{                                                                           /*colisões na célula.*/
                                                                            /*Se não existirem colisões na célula, adicionar */
                                                                            /*nova colisão.*/
                                                                            /*Se sim, procurar pela palavra a ser adicionada.*/
                                                                            /*Se a palavra existir, adicionar um novo arquivo.*/
                                                                            /*Se não, adicionar nova colisão.*/
    if(colisoes == NULL)
    {
        printf("Adicionando primeira colisao.\n");
        colisoes = new NoColisao(palavra);
        colisoes->AdicionarArquivo(arquivo, local);
        contador++;
        printf("Colisão adicionada.\n");
        return;
    }

    NoColisao* p = colisoes;

    while(true)
    {
        if(p->prox == NULL)
            break;

        if(!strcmp(p->palavra, palavra))
            break;

        p = p->prox;
    }

    if(p->prox == NULL)
    {
        p->prox = new NoColisao(palavra);
        p->AdicionarArquivo(arquivo, local);
        contador++;
        printf("\tAdicionando nova colisão.\n");
    }
    else
        p->AdicionarArquivo(arquivo, local);
}
bool Hashish::Celula::Pesquisa(ModulodePesquisa* conteiner) /*Pesquisar dentro da célula por uma palavra específica.*/
{                                                           /*Se a palavra for encontrada, incorporar lista de arquivos */
                                                            /*no módulo de pesquisa e retornar true. Se não, false.*/
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
    printf(" %d.\n", AgregarValor(item));
    tabela[AgregarValor(item)].AdicionarOcorrencia(item, arquivo, local);
}
void Hashish::Pesquisa(ModulodePesquisa* conteiner) /*Anular o conteiner caso nenhum resultado for encontrado durante a pesquisa.*/
{
    if(tabela[AgregarValor(conteiner->palavra)].Pesquisa(conteiner))
        return;
    conteiner = NULL;
}


