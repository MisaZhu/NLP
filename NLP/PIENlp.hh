#ifndef PIE_NLP_HH
#define PIE_NLP_HH

#include <stack>
#include "Purpose.hh"
#include "Input.hh"
#include "NLPReader.hh"
#include "PurposeCreator.hh"

using namespace std;


class PIENlp {

	bool terminated;

	Purpose* currentPurpose;
	NLPReader* reader;
	PurposeCreator* purposeCreator;

	stack<Purpose*> purposeStack;

	void terminate();

	Purpose* purposeChanged(Input* input);

public:

	PIENlp() {
		terminated = false;
		currentPurpose = NULL;
		reader = NULL;
		purposeCreator = NULL;
	}

	bool isTerminated();

	void run();

	void setPurposeCreator(PurposeCreator* purposeCreator); 

	void setReader(NLPReader* r); 

	stack<Purpose*>* getPurposeStack();

};



#endif
