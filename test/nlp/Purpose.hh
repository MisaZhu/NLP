#ifndef PURPOSE_HH
#define PURPOSE_HH

#include <string>
#include <vector>

#include "Input.hh"

using namespace std;

class PurposeInput {
	string type;
};


class Purpose {
	string purpose;
	vector <PurposeInput> inputItems; // expected inputs
	
public:
	bool checkInput(Input* input);

	bool ready();

	static Purpose *newPurpose(Input* input);
};

#endif
