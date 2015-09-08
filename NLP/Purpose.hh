#ifndef PURPOSE_HH
#define PURPOSE_HH

#include <string>
#include <vector>

#include "Input.hh"

using namespace std;

class Purpose {
protected:
	size_t id;
	
public:
	Purpose() {
		id = 0;
	}

	Purpose(size_t id) {
		setID(id);
	}

	void setID(size_t id) {
		this->id = id;
	}

	size_t getID() {
		return id;
	}

	virtual ~Purpose() { }

	virtual bool checkInput(Input* input) = 0;

	virtual bool ready() = 0;

	virtual void moreInput() = 0;

	virtual void suspend() = 0;

	virtual void resume() = 0;

	virtual bool keepInStack() = 0;

	virtual Input* execute() = 0;
};

#endif
