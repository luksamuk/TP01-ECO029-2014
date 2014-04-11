// IMPORTANTE: ESTE ARQUIVO <<<<DEVE>>>> SER SALVO COM CODIFICAÇÃO
// WESTERN WINDOWS 1252 (ou ANSI), OU A REMOÇÃO DE CARACTERES ESPECIAIS NÃO
// FUNCIONARÁ!!!!

#include "TextPool.h"

TextPool::TextPool()
{
	m_texts = m_preprocessed = NULL;
	m_textsnumber = 0;

	// Open robots.txt
	char* buffer;
	FILE* robots = fopen("robots.txt", "r");
	if(robots)
	{
		// Get the size of the text file in bytes
		fseek(robots, 0L, SEEK_END);
		long int size = ftell(robots);
		rewind(robots);

		// Get file contents as string
		buffer = new char[size];
		fread(buffer, size, 1, robots);
		rewind(robots);

		// Get number of files stored on text
		char* p, *q;
		p = q = buffer;
		while(*p != '\0')
		{
			if((*p == '\n' || *p == '\0') && (p - q) > 1)
			{
				q = p;
				m_textsnumber++;
			}
			p++;
		}
		delete [] buffer;

		#ifdef DEBUG
		printf("Grabbed names for %d files.\n", m_textsnumber);
		#endif

		// Allocate filenames and etc for each file
		m_filenames    = new char*[m_textsnumber];
		m_texts        = new char*[m_textsnumber];
		m_preprocessed = new char*[m_textsnumber];
		m_filesizes    = new long int[m_textsnumber];

		// Store filenames
		for(int i = 0; i < m_textsnumber; i++)
		{
			m_filenames[i] = new char[255];
			fscanf(robots, "%s", m_filenames[i]);
			#ifdef DEBUG
			printf("Grabbed filename \"%s\";\n", m_filenames[i]);
			#endif
		}
		fclose(robots);

		// Load text from files
		FILE* fp;
		for(unsigned int n_f = 0; n_f < m_textsnumber; n_f++)
		{
			#ifdef DEBUG
			printf("Grabbing contents of \"%s\"\n", m_filenames[n_f]);
			#endif
			fp = fopen(m_filenames[n_f], "r");
			fseek(fp, 0L, SEEK_END);
			size = ftell(fp);
			rewind(fp);
			m_filesizes[n_f] = size;

			m_texts[n_f]        = new char[size];
			m_preprocessed[n_f] = new char[size];
			fread(m_texts[n_f], size, 1, fp);
			strcpy(m_preprocessed[n_f], m_texts[n_f]);
			fclose(fp);

			#ifdef DEBUG
			printf("Creating processed copy of \"%s\"\n", m_filenames[n_f]);
			#endif

			// Remove special characters
			RemoveOddCharacters(m_preprocessed[n_f], size);

			#ifdef DEBUG
			printf(KGRN "Normal:" KRESET "\n%s\n" KGRN "Preprocessed:" KRESET "\n%s\n", m_texts[n_f], m_preprocessed[n_f]);
			#endif

			#ifdef DEBUG
			printf("All set for this file.\n");
			#endif
		}
	}
}

TextPool::~TextPool()
{
	for(unsigned int i = 0; i < m_textsnumber; i++)
	{
		#ifdef DEBUG
		printf("Deleting copy of "KGRN"%s"KRESET"...\n", m_filenames[i]);
		#endif
		delete [] m_filenames[i];
		delete [] m_texts[i];
		delete [] m_preprocessed[i];
	}
	delete [] m_filenames;
	delete [] m_texts;
	delete [] m_preprocessed;
	delete [] m_filesizes;
	#ifdef DEBUG
	printf(KMAG"All deleted.\n"KRESET);
	#endif
}

unsigned int TextPool::GetTextsNumber() const
{
	return m_textsnumber;
}

const char* TextPool::GetPreprocessedText(unsigned int idx) const
{
	if(m_textsnumber < idx) return NULL;
	return m_preprocessed[idx];
}

const char* TextPool::GetText(unsigned int idx) const
{
	if(m_textsnumber < idx) return NULL;
	return m_preprocessed[idx];
}

const char* TextPool::GetFilename(unsigned int idx) const
{
	if(m_textsnumber < idx) return NULL;
	return m_filenames[idx];
}

void TextPool::RemoveOddCharacters(char* text, long int size)
{
	if(!text) return;
	for(long int i = 0; i < size; i++)
	{
		switch(text[i])
		{
		case 'á':
		case 'à':
		case 'â':
		case 'ã':
		case 'Á':
		case 'À':
		case 'Â':
		case 'Ã':
			text[i] = 'a';
			break;
		case 'ç':
		case 'Ç':
			text[i] = 'c';
			break;

		case 'é':
		case 'è':
		case 'ê':
		case 'É':
		case 'È':
		case 'Ê':
			text[i] = 'e';
			break;

		case 'í':
		case 'ì':
		case 'Í':
		case 'Ì':
			text[i] = 'i';
			break;

		case 'ó':
		case 'ò':
		case 'ô':
		case 'õ':
		case 'Ó':
		case 'Ò':
		case 'Ô':
		case 'Õ':
			text[i] = 'o';
			break;

		case 'ú':
		case 'ù':
		case 'Ú':
		case 'ü':
		case 'Ù':
		case 'Ü':
			text[i] = 'u';
			break;

		// Special symbols
		case '!':
		case '?':
		case ':':
		case ';':
		case '.':
			text[i] = ' ';
			break;
		default: break;
		}
		// Remove upper case
		if(text[i] >= 'A' && text[i] <= 'Z')
			text[i] += 32;
	}
}

long int TextPool::GetTextLength(unsigned int txt) const
{
	if(txt > m_textsnumber) return 0;
	return m_filesizes[txt];
}

char* TextPool::m_grabtextcopy(unsigned int txt)
{
	char* cpy = new char[GetTextLength(txt)];
	for(long int i = 0; i < GetTextLength(txt); i++)
		cpy[i] = m_preprocessed[txt][i];
	return cpy;
}

void TextPool::RegisterWordsOnHash(Hashish* h)
{
	char* pch;
	const char tokens[] = " \"\',.()[]<>{}?:;!-\n";
	for(unsigned int i = 0; i < m_textsnumber; i++)
	{
		char* txt = m_grabtextcopy(i);
		#ifdef DEBUG
		printf("Adding" KRED " %s " KRESET "to hash...\n", GetFilename(i));
		#endif
		pch = strtok(txt, tokens);
		#ifdef DEBUG
		printf("Tokenized.\n");
		#endif
		while(pch != NULL)
		{
			#ifdef DEBUG
			printf("Adding word "KGRN"%s"KRESET" to hash...", pch);
			#endif
			h->Adicionar(pch, i, (pch - txt));
			#ifdef DEBUG
			printf("Ok\n");
			#endif
			pch = strtok(NULL, tokens);
		}
		#ifdef DEBUG
		printf("Ok.\n");
		#endif
	}
}