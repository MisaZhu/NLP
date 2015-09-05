#ifndef MY_PURPOSE_HH
#define MY_PURPOSE_HH

#include "NLP.hh"
#include "TinyJSON.hh"


typedef struct {
	string value;
	string ask;
} MyInput;

class MyPurpose : public Purpose {
	JSONEntry* purposeJSON;
	NLP* nlp;
	map<string, MyInput> inputs;
	vector<string> readyCond;
	string tryInput;
	string name;

	bool fetchInput(const string& name, const string& input, string& value);

	bool checkReady(const string& cond);

	void talk(const string& text);

public:

	MyPurpose(NLP* n, JSONEntry* json) {
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
};

#endif
