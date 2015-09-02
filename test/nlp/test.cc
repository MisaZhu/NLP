#include <iostream>
#include <map>
#include "NLP.hh"

using namespace std;

class StdReader : public NLPReader {
public:
	Input* read() {
		string r;
		std::cin >> r;
		if(r.length() == 0)
			return NULL;

		return new Input(r);
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

	Input* execute() {
		std::cout << "execute: " << purpose << "\n";
		return NULL;
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
	StdReader reader;
	PurposeC pc;

	nlp.setReader(&reader);
	nlp.setPurposeCreator(&pc);
	nlp.run();

	return 0;
}
