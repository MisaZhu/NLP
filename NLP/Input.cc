#include "Input.hh"

const string& Input::getText() {
	return text;
}


void Input::setText(const string& t) {
	text = t;
}

Input::Input() {
	text = "";
}

Input::Input(const string& t) {
	setText(t);
}
