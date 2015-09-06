#ifndef SIMPLE_PURPOSE_HH
#define SIMPLE_PURPOSE_HH

#include "NLP.hh"
#include "TinyJSON.hh"


typedef struct {
	string value;
	string ask;
} MyInput;

class SimplePurpose : public Purpose {
	JSONEntry* purposeJSON;
	NLP* nlp;
	map<string, MyInput> inputs;
	vector<string> readyCond;
	string inputExpected;
	string name;

	bool fetchInput(const string& name, const string& input, string& value);

	bool checkReady(const string& cond);

	void talk(const string& text);

	bool inStack;

public:

	SimplePurpose(NLP* n, JSONEntry* json) {
		inStack = false;
		purposeJSON = json;
		nlp = n;
	}

	void suspend();

	void resume();

	bool checkInput(Input* input);

	void moreInput();

	bool ready();

	Input* execute();

	bool init();

	bool keepInStack();
};

#endif
