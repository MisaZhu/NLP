#include "Purpose.hh"


bool Purpose::ready() {
	return true;
}

bool Purpose::checkInput(Input* input) {
	return false;
}

Purpose* Purpose::newPurpose(Input* input) {
	return NULL;
}
