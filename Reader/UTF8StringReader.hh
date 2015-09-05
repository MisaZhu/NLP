#ifndef UTF8StringReader_hh
#define UTF8StringReader_hh

#include "UTF8Reader.hh"
#include "StreamByteReader.hh"
#include <sstream>


class UTF8StringReader : public UTF8Reader {
	StreamByteReader ssReader;
	std::istringstream strStream;

public:
	UTF8StringReader();

	UTF8StringReader(const std::string& str);

	void setString(const std::string& str);
};


#endif
