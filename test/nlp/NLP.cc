#include "NLP.hh"

using namespace std;

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

	return Purpose::newPurpose(input);
}

void NLP::run() {
	if(input == NULL)
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
			execute();
			currentPurpose = purposeStack.top();
			if(currentPurpose != NULL)
				purposeStack.pop();
		}
	}
}



