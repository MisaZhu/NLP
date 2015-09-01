#ifndef INPUT_HH
#define INPUT_HH

#include <string>

using namespace std;

class Input {

protected:
	string content;

public:
	virtual bool read() = 0;

	const string& getContent();
};

#endif
