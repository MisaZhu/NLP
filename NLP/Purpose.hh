#ifndef PURPOSE_HH
#define PURPOSE_HH

#include <string>
#include <vector>

#include "Input.hh"

using namespace std;

class Purpose {
protected:
	string purpose;
	
public:
	virtual ~Purpose() { }

	virtual bool checkInput(Input* input) = 0;

	virtual bool ready() = 0;

	virtual void moreInput() = 0;

	virtual void suspend() = 0;

	virtual void resume() = 0;

	virtual Input* execute() = 0;
};

#endif
