#ifndef PURPOSE_CREATOR_HH
#define PURPOSE_CREATOR_HH


#include "Purpose.hh"

class PIENlp;

class PurposeCreator {
public :
	virtual Purpose* newPurpose(PIENlp* nlp, Input* input) = 0;	
	
	virtual Purpose* newPurpose(PIENlp* nlp, size_t id) = 0;	

	virtual size_t getPurposeID(PIENlp* nlp, Input* input) = 0;	
};


#endif
