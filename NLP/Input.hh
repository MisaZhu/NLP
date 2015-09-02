#ifndef INPUT_HH
#define INPUT_HH

#include <string>

using namespace std;

class Input {
protected:
	string content;

public:
	Input(const string &r);

	const string& getContent();

	void setContent(const string & r);
};

#endif
