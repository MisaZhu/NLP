#include "Reader.hh"

Reader::Reader() {
	setByteReader(null);
}

void Reader::setByteReader(ByteReader* r) {
	byteReader = r;
}
