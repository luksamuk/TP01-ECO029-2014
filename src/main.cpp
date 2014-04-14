#include "TextPool.h"
#include "Hash.h"

int main(void)
{
	TextPool t;
	Hashish h(10000);
	t.RegisterWordsOnHash(&h);
	printf("Done with adding shit.\n");
/*
	ModulodePesquisa* m;
	unsigned int entrada;
	printf(KRED"ATENCAO:"KRESET" Verifique se o seu terminal ou prompt de comando "
		   "utiliza codificacao ANSI/WINDOWS-1252.\n");

	do
	{
		printf("Selecione a opcao de pesquisa.\n"
			KMAG"1."KRESET" Pesquisa por palavra\n"
			KMAG"2."KRESET" Pesquisa por frase\n"
			KMAG"0."KRESET" Sair\n");

		scanf("%d", &entrada);

		switch(entrada)
		{
		case 1: // Pesquisa por palavra
			char buf[255], procbuf[255];
			printf(KCYN"Digite a palavra procurada:\n"KRESET);
			scanf("%s", buf);

			strcpy(procbuf, buf);
			TextPool::RemoveOddCharacters(procbuf, strlen(procbuf));
			sscanf(procbuf, "%s", procbuf);


			m = new ModulodePesquisa;
			m->Palavra_Chave = procbuf;
			h.Pesquisa(m);

			printf("\nResultado da busca \""KCYN"%s"KRESET"\"\n", m->palavra);
			if(!m->listatexto)
				printf(KRED"ERRO: "KRESET"Palavra nao encontrada.\n\n");
			else
			{

			}

			strcpy(procbuf, "");
			break;
		case 2: // Pesquisa por frase
			break;
		case 0: // Sair
			printf(KGRN"Saindo...\n"KRESET);
			break;
		default: // Erro
			printf(KRED"Erro:"KRESET" Opcao "KYEL"%d"KRESET" desconhecida.\n", entrada);
			break;
		}
	}
	while(entrada != 0);

*/
	return 0;
}
