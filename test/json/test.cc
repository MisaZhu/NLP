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


  std::filebuf fb;
	fb.open ("conf.json",std::ios::in);
	std::istream is(&fb);

	byteReader.setInputStream(&is);
	reader.setByteReader((ByteReader*) &byteReader);


	while(true) {
		is.seekg(0);
		TinyJSON json;
		json.setReader(&reader);

		JSONElm *elm = json.parse();
		delete elm;
	}

	return 0;
}


