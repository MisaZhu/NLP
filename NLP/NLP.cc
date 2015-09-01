#include "NLP.hh"

using namespace std;

void NLP::setPurposeCreator(PurposeCreator* pc) {
	purposeCreator = pc;
}

stack<Purpose*>* NLP::getPurposeStack() {
	return &purposeStack;
}

void NLP::setInput(Input* input) {
	this->input = input;
}

void NLP::terminate() {
	terminated = true;
}

bool NLP::isTerminated() {
	return terminated;
}

void NLP::execute() {
}

Purpose* NLP::purposeChanged() {
	if(input == NULL)
		return NULL;

	if(currentPurpose != NULL && currentPurpose->checkInput(input)) {
		return currentPurpose;
	}

	if(purposeCreator != NULL)
		return purposeCreator->newPurpose(this, input);

	return NULL;
}

void NLP::run() {
	if (purposeCreator == NULL || input == NULL)
		return;

	while(!isTerminated()) {
		if(!input->read())
			continue;

		Purpose *purpose = purposeChanged();

		if(purpose != NULL && purpose != currentPurpose) {
			purposeStack.push(purpose);
			currentPurpose = purpose;
		}

		if(currentPurpose != NULL && currentPurpose->ready()) {
			currentPurpose->execute();
			purposeStack.pop();

			delete currentPurpose;
			currentPurpose = NULL;

			if(purposeStack.size() > 0)
				currentPurpose = purposeStack.top();
		}
	}
}



