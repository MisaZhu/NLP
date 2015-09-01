#ifndef NLP_HH
#define NLP_HH

#include <stack>
#include "Purpose.hh"

using namespace std;


class NLP {
	bool terminated;
	Purpose* currentPurpose;

	stack<Purpose*> purposeStack;

	void updatePurpose();

	void execute();

	void terminate();

	Purpose* purposeChanged(const Input& input);

	bool ready();

public:

	NLP() {
		terminated = false;
		currentPurpose = NULL;
	}

	bool isTerminated();

	void run();
};



#endif
