#include "../List.cpp"
#include <stdio.h>

void ImprimirVetor(int* vetor, unsigned long tam)
{
    for(int c=0; c<tam; c++)
    {
        if(!(c%5))
            printf("\n");
        printf("%d\t", vetor[c]);
    }
    printf("\n");
}

int main()
{
    List<int, char> lista;
    int* vetor;
    int* n;

    lista.Insert(1, 'a');
    lista.Insert(2, 'b');
    lista.Insert(3, 'c');
    lista.Insert(4, 'd');
    lista.Insert(5, 'e');
    lista.Insert(6, 'f');
    lista.Insert(7, 'g');
    lista.Insert(8, 'h');
    lista.Insert(9, 'i');
    lista.Insert(10, 'j');
    lista.Insert(11, 'k');
    lista.Insert(12, 'l');
    lista.Insert(13, 'm');
    lista.Insert(14, 'n');
    lista.Insert(15, 'o');

    printf("Lista:");
    vetor = lista.DataVector(NULL);
    ImprimirVetor(vetor, lista.Length());

    n = lista.Search('c');
    if(n)
        printf("%d\n", *n);
    else
        printf("NULL\n");

    *n = 30;

    vetor = lista.DataVector(NULL);
    ImprimirVetor(vetor, lista.Length());

    delete [] vetor;
    return 0;
}
