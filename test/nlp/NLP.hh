#ifndef NLP_HH
#define NLP_HH

#include <stack>
#include "Purpose.hh"

using namespace std;


class NLP {

	bool terminated;

	Input* input;

	Purpose* currentPurpose;

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
	}

	bool isTerminated();

	void run();

	void setInput(Input* input); 

};



#endif
