#ifndef PURPOSE_HH
#define PURPOSE_HH

#include <string>
#include <vector>

using namespace std;

class Input {
	string content;

public:
	bool read() {
		return true;
	}
};

class PurposeInput {
	string type;
};


class Purpose {
	string purpose;
	vector <PurposeInput> inputItems; // expected inputs
	
public:
	bool checkInput(const Input& input);

	bool ready();

	static Purpose *newPurpose(const Input& input);
};

#endif
