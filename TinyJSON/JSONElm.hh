#ifndef JSONELM_HH
#define JSONELM_HH

#include <string>
#include <map>
#include <vector>
#include "utils.hh"

using namespace std;

class JSONElm {
public:
	static const Byte OBJ = 0;
	static const Byte ARRAY = 1;
	static const Byte TEXT = 2;

	Byte type;

	string name;

	string text;
	JSONElm *object;
	vector<JSONElm*> array;

	map<std::string, JSONElm*> children;

	inline JSONElm() {
		type = OBJ;
		object = NULL;
	}

	~JSONElm();

};


#endif
