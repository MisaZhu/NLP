#ifndef UTF8Reader_hh
#define UTF8Reader_hh

#include "Reader.hh"


class UTF8Reader : public Reader {
	Byte* ret;
	Byte rollBackByte;
	int bufSize;

	static const int WORD_STEP_LEN = 32;

public:

	inline UTF8Reader() {
		rollBackByte = 0;
		bufSize = WORD_STEP_LEN + 1;
		ret = new Byte[bufSize];
	}

	inline ~UTF8Reader() {
		if(ret != NULL) {
			delete ret;
			ret = NULL;
		}
	}

	virtual const Byte* readSingleWord(int & len, bool &ascii);

	virtual const Byte* readTill(int & len, Byte stop);

	virtual const Byte read();
};


#endif
