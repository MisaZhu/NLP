#include "NLP.hh"

using namespace std;

void NLP::setPurposeCreator(PurposeCreator* pc) {
	purposeCreator = pc;
}

void NLP::setReader(NLPReader* r) {
	reader = r;
}


stack<Purpose*>* NLP::getPurposeStack() {
	return &purposeStack;
}

void NLP::terminate() {
	terminated = true;
}

bool NLP::isTerminated() {
	return terminated;
}

Purpose* NLP::purposeChanged(Input* input) {
	if(input == NULL ||
			(currentPurpose != NULL && currentPurpose->checkInput(input))) {
		return currentPurpose;
	}

	if(purposeCreator != NULL) {
		Purpose *ret = purposeCreator->newPurpose(this, input);
		ret->checkInput(input);
		return ret;
	}

	return NULL;
}

void NLP::run() {
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
			if(currentPurpose != NULL)
				currentPurpose->suspend();

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



