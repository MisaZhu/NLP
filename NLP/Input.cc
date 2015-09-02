#include "Input.hh"

const string& Input::getType() {
	return type;
}


void Input::setType(const string& t) {
	type = t;
}

Input::Input() {
	type = "";
}

Input::Input(const string& t) {
	setType(t);
}
