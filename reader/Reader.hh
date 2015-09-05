#ifndef Reader_hh
#define Reader_hh

#include "utils.hh"
#include "ByteReader.hh"

class Reader {
protected:
	ByteReader *byteReader;
public:
	Reader();
	void setByteReader(ByteReader* r);
	virtual const Byte* readSingleWord(int & len, bool &ascii, bool ignore = false) = 0;
	virtual const Byte read() = 0;
	virtual const Byte* readTill(int & len, Byte stop) = 0;
};


#endif
