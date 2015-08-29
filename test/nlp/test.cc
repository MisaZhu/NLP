#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "UTF8Reader.hh"
#include "StreamByteReader.hh"

extern "C" {
//#include "unqlite.h"
}

using namespace std;

class Input {
	string req;
	vector <string> input;
};

class Purpose {
	string purpose;
	map <string, Input> inputSet;
};


class NLP {
	unsigned long steps;
	vector<Purpose> purposes;
};

void input(string in, NLP &nlp) {
}

void updatePurpose(NLP& nlp) {

}

void excute(NLP& nlp) {
}


int main(int argc, char** argv) {
	NLP nlp;

	while(true) {
		string in = "";
		input(in, nlp);
		updatePurpose(nlp);
		excute(nlp);
	}
	return 0;
}
