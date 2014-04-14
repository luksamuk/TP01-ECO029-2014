//Templates genéricos de lista dinâmica simples.
//Com amor,
//~zanv.

#ifndef LIST_CPP_INCLUDED
#define LIST_CPP_INCLUDED
#include <stddef.h>
#include <stdio.h>
template<typename T>
class VectorList    /*Somente insere elementos, sem remoção nem pesquisa.*/
{                   /*Gera um vetor com todos os dados inseridos para iteração.*/
private:
    struct node
    {
        T data;
        node* next;
    };
    unsigned long length;
    node* list;
    node* last;

public:
    VectorList();
    ~VectorList();
    void Insert(T);
    T* DataVector(unsigned long*);
    unsigned long Length();
};

template<typename T, typename I>
class List  /*Somente insere elementos, mas oferece a opção de pesquisa.*/
{           /*A função de pesquisa dá acesso ao ponteiro interno com os dados para possíveis alterações.*/
            /*Conta com a mesma função de acesso aos dados do container da VectorList.*/
            /*O indexador somente identifica os nós, sendo assim, o vetor gerado por T* DataVector */
            /*estará sempre na ordem de inserções.*/
private:
    struct node
    {
        T data;
        I index;
        node* next;
    };
    unsigned long length;
    node* list;
    node* last;

public:
    List();
    ~List();
    T* Insert(T, I);
    T* Search(I);
    T* DataVector(unsigned long*);
    unsigned long Length();
};

/*
**
**
**
*/

template<typename T>
VectorList<T>::VectorList()
{
    list = NULL;
    last = list;
    length = 0;
}

template<typename T>
VectorList<T>::~VectorList()
{
    if(list)
    {
        if(list->next == NULL)
        {
            delete list;
            list = NULL;
        }
        else
        {
            node* next_p;
            next_p = list->next;

            while(list->next != NULL)
            {
                delete list;
                list = next_p;
                next_p = list->next;
            }

            delete list;
            list = NULL;
            length = 0;
        }
    }
}

template<typename T>
void VectorList<T>::Insert(T new_data)
{
    if(list == NULL)
    {
        list = new node;
        list->next = NULL;
        list->data = new_data;
        last = list;
    }
    else
    {
        last->next = new node;
        last = last->next;
        last->next = NULL;
        last->data = new_data;
    }
    length++;
}

template<typename T>
T* VectorList<T>::DataVector(unsigned long* size)
{
    if(size)
        *size = length;

    if(length)
    {
        T* vector = new T[length];
        node* p = list;

        for(int c = 0; c < length; c++)
        {
            vector[c] = p->data;
            p = p->next;
        }

        return vector;
    }

    return NULL;
}

template<typename T>
unsigned long VectorList<T>::Length()
{
    return length;
}

/*
**
*/

template<typename T, typename I>
List<T,I>::List()
{
    list = NULL;
    last = list;
    length = 0;
}

template<typename T, typename I>
List<T,I>::~List()
{
    if(list)
    {
        if(list->next == NULL)
        {
            delete list;
            list = NULL;
        }
        else
        {
            node* next_p;
            next_p = list->next;

            while(list->next != NULL)
            {
                delete list;
                list = next_p;
                next_p = list->next;
            }

            delete list;
            list = NULL;
            length = 0;
        }
    }
}

template<typename T, typename I>
T* List<T,I>::Insert(T new_data, I index)
{
    if(list == NULL)
    {
        list = new node;
        list->next = NULL;
        list->data = new_data;
        list->index = index;
        last = list;
    }
    else
    {
        last->next = new node;
        last = last->next;
        last->next = NULL;
        last->index = index;
        last->data = new_data;
    }
    length++;
    return &last->data;
}

template<typename T, typename I>
T* List<T,I>::Search(I index)
{
    node* p = list;

    while(true)
    {
        if(p == NULL)
            break;

        if(p->index == index)
            return &p->data;

        p = p->next;
    }
    return NULL;
}

template<typename T, typename I>
T* List<T,I>::DataVector(unsigned long* size)
{
    if(size)
        *size = length;

    if(length)
    {
        T* vector = new T[length];
        node* p = list;

        for(int c = 0; c < length; c++)
        {
            vector[c] = p->data;
            p = p->next;
        }

        return vector;
    }

    return NULL;
}

template<typename T, typename I>
unsigned long List<T,I>::Length()
{
    return length;
}

#endif // LIST_CPP_INCLUDED
