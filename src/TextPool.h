#ifndef TEXTPOOL_H
#define TEXTPOOL_H

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
public:
	TextPool();
	~TextPool();

	unsigned int GetTextsNumber(void)              const;
	const char*  GetPreprocessedText(unsigned int) const;
	const char*  GetText(unsigned int)             const;
	const char*  GetFilename(unsigned int)         const;

	static void RemoveOddCharacters(char*, long int);
};


#endif