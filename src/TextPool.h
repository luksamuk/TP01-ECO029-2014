#ifndef TEXTPOOL_H
#define TEXTPOOL_H

#define KNRM   "\x1B[0m"
#define KRED   "\x1B[31m"
#define KGRN   "\x1B[32m"
#define KYEL   "\x1B[33m"
#define KBLU   "\x1B[34m"
#define KMAG   "\x1B[35m"
#define KCYN   "\x1B[36m"
#define KWHT   "\x1B[37m"
#define KRESET "\033[0m"


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

	void         RegisterWordsOnHash(Hashish&);

	static void RemoveOddCharacters(char*, long int);
};


#endif