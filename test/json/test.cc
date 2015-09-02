#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "UTF8Reader.hh"
#include "StreamByteReader.hh"

#include "TinyJSON.hh"

using namespace std;

int main(int argc, char** argv) {

  UTF8Reader reader;
	StreamByteReader byteReader;

	byteReader.setInputStream((std::istream*)&std::cin);
	reader.setByteReader((ByteReader*) &byteReader);


	TinyJSON json;
	json.setReader(&reader);

	JSONElm *elm = json.parse();

	string s;
	TinyJSON::dump(*elm, s);
	std::cout << s << "\n";

	delete elm;

	return 0;
}


