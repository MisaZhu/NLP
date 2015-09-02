#ifndef NLP_READER_HH
#define NLP_READER_HH

#include "Input.hh"

class NLPReader {
public:
	virtual Input* read() = 0;
};

#endif
