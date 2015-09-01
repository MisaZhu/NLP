#ifndef NLP_HH
#define NLP_HH

#include <stack>
#include "Purpose.hh"
#include "PurposeCreator.hh"

using namespace std;


class NLP {

	bool terminated;

	Input* input;

	Purpose* currentPurpose;
	PurposeCreator* purposeCreator;

	stack<Purpose*> purposeStack;

	void updatePurpose();

	void execute();

	void terminate();

	Purpose* purposeChanged();

	bool ready();

public:

	NLP() {
		terminated = false;
		input = NULL;
		currentPurpose = NULL;
		purposeCreator = NULL;
	}

	bool isTerminated();

	void run();

	void setInput(Input* input); 

	void setPurposeCreator(PurposeCreator* purposeCreator); 

	stack<Purpose*>* getPurposeStack();

};



#endif
