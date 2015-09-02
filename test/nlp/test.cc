#include <iostream>
#include <map>
#include "NLP.hh"
#include "UTF8Reader.hh"
#include "StreamByteReader.hh"


using namespace std;

class InputTest : public Input {
	vector<string> words;
public:
	vector<string>* getWords() {
		return &words;
	}
};

class StdReader : public NLPReader {
  UTF8Reader reader;
	StreamByteReader byteReader;
	
public:
	StdReader() {
		byteReader.setInputStream((std::istream*)&std::cin);
		reader.setByteReader((ByteReader*) &byteReader);
	}

	Input* read() {
		int len;
		bool ascii;
		InputTest* in = NULL;

		while(true) {
			const Byte* sw = reader.readSingleWord(len, ascii);
			
			if(len == 0)
				break;

			if(ascii && sw[0] == '\n')
				break;

			string s((const char*)sw);

			if(in == NULL) {
				in = new InputTest();
				in->setType(s);
			}

			in->getWords()->push_back(s);
		}

		return in;
	}
};

class PurposeTest : public Purpose {
	map<string, string> inputItems;
public:

	PurposeTest(const string& p) {
		purpose = p;
		inputItems.insert(map < string, string >::value_type(p, ""));
	}

	void suspend() {
	}
	
	void resume() {
	}


	bool checkInput(Input* input) {
		string in = input->getType();
		map<string, string>::iterator it = inputItems.find(in);

		if(it == inputItems.end()) {
			return false;
		}

		it->second = in;
		return true;
	}

	void moreInput() {
		std::cout << "more input ?\n";
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
		string in = input->getType();
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
