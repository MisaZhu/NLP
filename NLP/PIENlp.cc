#include "PIENlp.hh"

using namespace std;

void PIENlp::setPurposeCreator(PurposeCreator* pc) {
	purposeCreator = pc;
}

void PIENlp::setReader(NLPReader* r) {
	reader = r;
}


vector<Purpose*>* PIENlp::getPurposes() {
	return &purposes;
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
		Purpose* ret = NULL;
		size_t id = purposeCreator->getPurposeID(this, input);
		for(vector<Purpose*>::iterator it = purposes.begin(); it != purposes.end(); ++it) {
			ret = *it;
			if(ret != NULL && ret->getID() == id) {
				purposes.erase(it);
				return ret;
			}
		}	

		ret = purposeCreator->newPurpose(this, id);
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
					purposes.erase(purposes.end()-1);
					delete currentPurpose;
				}
			}

			purposes.push_back(purpose);
			currentPurpose = purpose;
		}

		if(currentPurpose != NULL) {
			if(currentPurpose->ready()) {
				input = currentPurpose->execute();
				if(!currentPurpose->keepInStack()) {
					purposes.erase(purposes.end()-1);

					delete currentPurpose;
					currentPurpose = NULL;

					if(purposes.size() > 0)
						currentPurpose = *(purposes.end()-1);

					if(currentPurpose != NULL)
						currentPurpose->resume();
				}
			}
			else {
				currentPurpose->moreInput();
			}
		}
	}
}



