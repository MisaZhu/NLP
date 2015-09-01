#include "NLP.hh"

using namespace std;

void NLP::terminate() {
	terminated = true;
}

bool NLP::isTerminated() {
	return terminated;
}

void NLP::execute() {
}

Purpose* NLP::purposeChanged(const Input & input) {
	if(currentPurpose != NULL && currentPurpose->checkInput(input)) {
		return currentPurpose;
	}

	return Purpose::newPurpose(input);
}

void NLP::run() {
	while(!isTerminated()) {
		Input input;
		if(!input.read())
			continue;

		Purpose *purpose = purposeChanged(input);

		if(purpose != NULL && purpose != currentPurpose) {
			purposeStack.push(purpose);
			currentPurpose = purpose;
		}

		if(currentPurpose != NULL && currentPurpose->ready()) {
			execute();
			currentPurpose = purposeStack.top();
			if(currentPurpose != NULL)
				purposeStack.pop();
		}
	}
}



