#include "StreamByteReader.hh"

Byte StreamByteReader::read() {
	char b[2];

	if(stream == null)
		return 0;

	stream->read(b, 1);
	if((*stream)) {
		return (Byte)b[0];
	}

	return 0;
}
