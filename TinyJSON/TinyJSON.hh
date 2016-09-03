#ifndef TinyJSON_HH
#define TinyJSON_HH

#include "JSONEntry.hh"
#include "Reader.hh"

using namespace std;

class TinyJSON {
	static const Byte ELM = 0;
	static const Byte NAME = 1;
	static const Byte CONTENT = 3;
	Reader* reader;

	Byte state;

	bool readElm(JSONEntry& elm, Byte state = ELM);
public:

	void setReader(Reader* r) {
		reader = r;
	}

	bool parse(JSONEntry& elm);

	static bool parse(JSONEntry& elm, const string& str);
};

#endif
