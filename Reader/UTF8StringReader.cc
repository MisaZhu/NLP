#include <sstream>
#include "UTF8StringReader.hh"

UTF8StringReader::UTF8StringReader() {
	setString("");
}

UTF8StringReader::UTF8StringReader(const std::string& str) {
	setString(str);
}

void UTF8StringReader::setString(const std::string& str) {
	strStream.str(str);
	ssReader.setInputStream((std::istream*)&strStream);
	setByteReader((ByteReader*) &ssReader);
}
	
