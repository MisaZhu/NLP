#ifndef READER_HH
#define READER_HH

#include "utils.hh"

class Reader {

protected:
	virtual Byte readByte(); 

public:

	const char* readSingleWord(int & len);
};


#endif
