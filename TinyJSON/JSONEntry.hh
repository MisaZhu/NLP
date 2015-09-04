#ifndef JSONELM_HH
#define JSONELM_HH

#include <string>
#include <map>
#include <vector>
#include "utils.hh"

using namespace std;

class JSONEntry {
public:
	static const Byte OBJ = 0;
	static const Byte ARRAY = 1;
	static const Byte TEXT = 2;

	Byte type;

	string name;

	string text;
	JSONEntry *object;
	vector<JSONEntry*> array;

	map<std::string, JSONEntry*> children;

	inline JSONEntry() {
		type = OBJ;
		object = NULL;
	}

	~JSONEntry();

	JSONEntry* getChild(const string& name);
};


#endif
