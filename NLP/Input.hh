#ifndef INPUT_HH
#define INPUT_HH

#include <string>

using namespace std;

class Input {
	string text;

public:
	Input(const string &t);

	Input();

	const string& getText();

	void setText(const string & t);
};

#endif
