#ifndef StringReader_hh
#define StringReader_hh

#include "UTF8Reader.hh"
#include "StreamByteReader.hh"


class StringReader : public UTF8Reader {
	StreamByteReader ssReader;
	std::istringstream strStream;

public:
	StringReader();

	StringReader(const std::string& str);

	void setString(const std::string& str);
};


#endif
