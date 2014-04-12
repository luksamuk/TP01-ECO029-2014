//Template genérico de lista simples.
//Com amor,
//~zanv.

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <stddef.h>

template<typename T, typename I>
class List
{
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
    void Insert(T, I);
    bool Search(T*, I);
    T* DataVector(unsigned long*);
    unsigned long Length();
};

/*
**
**
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
void List<T,I>::Insert(T new_data, I index)
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
}

template<typename T, typename I>
bool List<T,I>::Search(T* data, I index)
{
    node* p = list;

    while(true)
    {
        if(p == NULL)
            break;

        if(p->index == index)
        {
            if(data)
                *data = p->data;
            return true;
        }

        p = p->next;
    }

    if(p == NULL)
        data = NULL;
    return false;
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
#endif // LIST_H_INCLUDED
