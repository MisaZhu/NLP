#include "Input.hh"

const string& Input::getContent() {
	return content;
}


void Input::setContent(const string& r) {
	content = r;
}

Input::Input(const string& r) {
	setContent(r);
}
