#ifndef PURPOSE_CREATOR_HH
#define PURPOSE_CREATOR_HH


#include "Purpose.hh"

class NLP;

class PurposeCreator {
public :
	virtual Purpose* newPurpose(NLP* nlp, Input* input) = 0;	
};


#endif
