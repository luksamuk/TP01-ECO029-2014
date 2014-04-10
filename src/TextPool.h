#ifndef TEXTPOOL_H
#define TEXTPOOL_H


#include "Hash.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

class TextPool
{
private:
	unsigned int m_textsnumber;
	char** m_filenames,
	    ** m_texts,
	    ** m_preprocessed;
	long int* m_filesizes;
	char* m_grabtextcopy(unsigned int);
public:
	TextPool();
	~TextPool();

	unsigned int GetTextsNumber(void)              const;
	const char*  GetPreprocessedText(unsigned int) const;
	const char*  GetText(unsigned int)             const;
	const char*  GetFilename(unsigned int)         const;
	long int     GetTextLength(unsigned int)       const;

	// TODO: The register func needs to be changed to:
	// Hashish::AdicionarOcorrencia(char* palavra, unsigned int texto, long int posicao)
	void         RegisterWordsOnHash(const Hashish&);

	static void RemoveOddCharacters(char*, long int);
};


#endif