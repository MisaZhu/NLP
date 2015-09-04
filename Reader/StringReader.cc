#include <sstream>
#include "StringReader.hh"

StringReader::StringReader() {
	setString("");
}

StringReader::StringReader(const std::string& str) {
	setString(str);
}

void StringReader::setString(const std::string& str) {
	strStream.str(str);
	ssReader.setInputStream((std::istream*)&strStream);
	setByteReader((ByteReader*) &ssReader);
}
	
