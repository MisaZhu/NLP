#include <fstream>

#include "UTF8Reader.hh"
#include "StreamByteReader.hh"

using namespace std;

int main(int argc, char** argv) {

  UTF8Reader reader;
	StreamByteReader byteReader;

	byteReader.setInputStream((std::istream*)&std::cin);
	reader.setByteReader((ByteReader*) &byteReader);
	
	int len;
	const Byte* r = reader.readTill(len, '?');
	std::cout << "[" << r << "]\n";
	reader.read();
	r = reader.readTill(len, '?');
	std::cout << "[" << r << "]\n";

	return 0;
}


