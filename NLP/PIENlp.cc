#include "PIENlp.hh"

using namespace std;

void PIENlp::setPurposeCreator(PurposeCreator* pc) {
	purposeCreator = pc;
}

void PIENlp::setReader(NLPReader* r) {
	reader = r;
}


stack<Purpose*>* PIENlp::getPurposeStack() {
	return &purposeStack;
}

void PIENlp::terminate() {
	terminated = true;
}

bool PIENlp::isTerminated() {
	return terminated;
}

Purpose* PIENlp::purposeChanged(Input* input) {
	if(input == NULL ||
			(currentPurpose != NULL && currentPurpose->checkInput(input))) {
		return currentPurpose;
	}

	if(purposeCreator != NULL) {
		Purpose *ret = purposeCreator->newPurpose(this, input);
		if(ret != NULL)
			ret->checkInput(input);
		return ret;
	}

	return NULL;
}

void PIENlp::run() {
	if (reader == NULL || purposeCreator == NULL)
		return;

	Input* input = NULL;

	while(!isTerminated()) {
		if(input == NULL) {
			input = reader->read();

			if(input == NULL)
				continue;
		}

		Purpose *purpose = purposeChanged(input);

		delete input;
		input = NULL;

		if(purpose != NULL && purpose != currentPurpose) {
			if(currentPurpose != NULL) {
				if(currentPurpose->keepInStack())
					currentPurpose->suspend();
				else {
					purposeStack.pop();
					delete currentPurpose;
				}
			}

			purposeStack.push(purpose);
			currentPurpose = purpose;
		}

		if(currentPurpose != NULL) {
			if(currentPurpose->ready()) {
				input = currentPurpose->execute();
				purposeStack.pop();

				delete currentPurpose;
				currentPurpose = NULL;

				if(purposeStack.size() > 0)
					currentPurpose = purposeStack.top();

				if(currentPurpose != NULL)
					currentPurpose->resume();
			}
			else {
				currentPurpose->moreInput();
			}
		}
	}
}



