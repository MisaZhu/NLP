#include <iostream>

#include "UTF8Reader.hh"
#include "StdByteReader.hh"

int main(int argc, char** argv) {
  UTF8Reader reader;
	StdByteReader byteReader;
	int len;
	bool ascii;

	reader.setByteReader((ByteReader*) &byteReader);

	while(true) {
		const Byte* sw = reader.readSingleWord(len, ascii);
		if(len == 0)
			break;

		if(ascii) {
			std::cout << " " << sw << " ";
		}
		else {
			std::cout << sw;
		}
	}
	std::cout << "\n";
	return 0;
}
