#ifndef PURPOSE_CREATOR_HH
#define PURPOSE_CREATOR_HH


#include "Purpose.hh"

class PIENlp;

class PurposeCreator {
public :
	virtual Purpose* newPurpose(PIENlp* nlp, Input* input) = 0;	
};


#endif
