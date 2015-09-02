#ifndef JSON_HH
#define JSON_HH

#include "JSONElm.hh"
#include "Reader.hh"

using namespace std;

class JSON {
	static const Byte ELM = 0;
	static const Byte NAME = 1;
	static const Byte CONTENT = 3;
	Reader* reader;

	Byte state;

	bool readElm(JSONElm& elm, Byte state = ELM);
public:

	void setReader(Reader* r) {
		reader = r;
	}

	JSONElm* parse();
};

#endif
