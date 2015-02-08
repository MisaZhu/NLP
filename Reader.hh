#ifndef Reader_hh
#define Reader_hh

#include "utils.hh"
#include "ByteReader.hh"

static const int MAX_WORD_LEN = 32;

class Reader {
	Byte ret[MAX_WORD_LEN + 1];
	Byte rollBackByte;



protected:
	ByteReader *byteReader;
public:

	inline Reader(ByteReader* r = null) {
		rollBackByte = 0;
		if(r != null)
			setByteReader(r);
	}

	inline void setByteReader(ByteReader* r) {
		byteReader = r;
	}

	//Read single word with UTF-8 encode
	const Byte* readSingleWord(int & len, bool &ascii);
};


#endif
