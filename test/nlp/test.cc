#include <iostream>
#include <map>
#include "NLP.hh"

using namespace std;

class StdInput : public Input {
public:
	bool read() {
		std::cin >> content;
		return true;
	}
};

class PurposeTest : public Purpose {
	map<string, string> inputItems;
public:

	PurposeTest(const string& p) {
		purpose = p;
		inputItems.insert(map < string, string >::value_type(p, ""));
	}

	bool checkInput(Input* input) {
		string in = input->getContent();
		map<string, string>::iterator it = inputItems.find(in);

		if(it == inputItems.end()) {
			return false;
		}

		it->second = in;
		return true;
	}

	bool ready() {
		map<string, string>::iterator it;

		it = inputItems.find(purpose);
		if(it == inputItems.end()) {
			return false;
		}
		
		string s = it->second;

		if(s == purpose)
			return true;
		return false;
	}	

	void execute() {
		std::cout << "execute: " << purpose << "\n";
	}
};

class PurposeC : public PurposeCreator {
public:
	Purpose* newPurpose(NLP* nlp, Input* input) {
		string in = input->getContent();
		std::cout << "new purpose: " << in << "\n";
		Purpose* ret = new PurposeTest(in); 
		return ret;
	}
};

int main(int argc, char** argv) {
	NLP nlp;
	StdInput input;
	PurposeC pc;

	nlp.setInput(&input);
	nlp.setPurposeCreator(&pc);
	nlp.run();

	return 0;
}
