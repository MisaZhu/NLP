#ifndef StreamByteReader_hh
#define StreamByteReader_hh


#include "ByteReader.hh"
#include <iostream>

class StreamByteReader : ByteReader {
	std::istream* stream;
public:
	inline StreamByteReader() {
		stream = null;
	}

	inline void setInputStream(std::istream *s) {
		stream = s;
	}

	Byte read();
};


#endif
