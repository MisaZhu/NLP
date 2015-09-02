#ifndef INPUT_HH
#define INPUT_HH

#include <string>

using namespace std;

class Input {
	string type;

public:
	Input(const string &t);

	Input();

	const string& getType();

	void setType(const string & t);
};

#endif
