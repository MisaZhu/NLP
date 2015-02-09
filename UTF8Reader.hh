#ifndef UTF8Reader_hh
#define UTF8Reader_hh

#include "Reader.hh"

static const int MAX_WORD_LEN = 32;

class UTF8Reader : public Reader {
	Byte ret[MAX_WORD_LEN + 1];
	Byte rollBackByte;

public:

	inline UTF8Reader() {
		rollBackByte = 0;
	}

	virtual const Byte* readSingleWord(int & len, bool &ascii);
};


#endif
