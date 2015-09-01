#include "Purpose.hh"


bool Purpose::ready() {
	return true;
}

bool Purpose::checkInput(const Input& input) {
	return false;
}

Purpose* Purpose::newPurpose(const Input& input) {
	return NULL;
}
