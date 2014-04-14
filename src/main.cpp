#include "TextPool.h"
#include "Hash.h"

int main(void)
{
	TextPool t;
	Hashish* h = new Hashish(10000);
	t.RegisterWordsOnHash(h);
	#ifdef DEBUG
	printf("Done with adding " KRED "shit.\n" KRESET);
	#endif

	ModulodePesquisa* m;

	unsigned int entrada;
	printf(KRED"ATENCAO:"KRESET" Ao utilizar acentos na pesquisa, verifique se o seu"
		" terminal ou prompt de comando utiliza codificacao ANSI/WINDOWS-1252.\n");

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

			//m = NULL; // DEBUG ONLY!!!!! REMOVE LATER!
			m = new ModulodePesquisa;
			m->Palavra_Chave = procbuf;
			h->Pesquisa(m);
			//TextPool::SortByRelevance(m); // ordenar a lista aqui.

			printf("\nResultado da busca \""KCYN"%s"KRESET"\"\n", procbuf);
			if(!m || !m->Contador_Arquivos)
				printf(KRED"ERRO: "KRESET"Palavra nao encontrada.\n\n");
			else
			{
				for(unsigned long i = 0; i < m->Contador_Arquivos; i++)
				{
					printf("%lu - " KGRN "%s" KRESET "\n", i + 1, t.GetFilename(m->Arquivos[i].Index));
					for(unsigned long j = 0; j < m->Arquivos[i].Contador; j++)
						t.PrintPhrase(m->Arquivos[i].Index, m->Arquivos[i].Ocorrencias[j]);
					printf("\n");
				}
			}
			//delete m;
			m = NULL;

			strcpy(procbuf, "");
			break;
		case 2: // Pesquisa por frase
			printf(KRED "ERRO: " KRESET "Funcao nao implementada. Desculpe pela inconveniencia.\n"
				"Para mais informacoes sobre o ocorrido, visite " KYEL "http://www.aiquedeliciacara.com/\n"
				KRESET);
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

	return 0;
}
