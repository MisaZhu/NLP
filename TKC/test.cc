#include <fstream>
#include <sstream>
#include <cstdlib>

#include "StringUtils.hh"
#include "UTF8Reader.hh"
#include "UTF8StringReader.hh"
#include "StreamByteReader.hh"


#include "MKNDict.hh"

using namespace std;


bool readMKNDict(const char* fname, MKNDict& dict) {

  UTF8Reader reader;
	StreamByteReader byteReader;

	std::fstream* stream;
	 
	stream = new fstream(fname, fstream::in);
	if(stream == null) 
		return false;

	byteReader.setInputStream(stream);
	reader.setByteReader((ByteReader*) &byteReader);

	while(true) {
		MKN mkn;

		string r = reader.readTill('|');
		r = StringUtils::trim(r);
		if(r.length() == 0)
			break;
		reader.read();
		std::cout << "[" << r << "] ";
		mkn.id = std::atoi(r.c_str());

		r = reader.readTill('|');
		if(r.length() == 0)
			break;
		reader.read();
		std::cout << "[" << r << "] ";
		mkn.label = r;



		r = reader.readTill('|');
		if(r.length() == 0)
			break;
		reader.read();
		std::cout << "[" << r << "] ";
		if(r[0] == '1')
			mkn.isLink = true;


		r = reader.readTill('|');
		if(r.length() == 0)
			break;
		reader.read();
		std::cout << "[" << r << "]\n";
		if(r[0] == '1')
			mkn.compressable = true;

		dict.add(mkn);
	}

	((fstream*)stream)->close();
	delete stream;
	return true;
}

int main(int argc, char** argv) {
	if(argc < 2) {
		std::cout << "Usage: test <dict fname>\n";
		return 1;
	}
	
	MKNDict dict;

	readMKNDict(argv[1], dict);

	MKN mkn;
	dict.get(1, mkn);

	return 0;
}


