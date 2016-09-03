#ifndef JSONELM_HH
#define JSONELM_HH

#include <string>
#include <map>
#include <vector>
#include "utils.hh"

using namespace std;

class JSONEntry {

	map<std::string, JSONEntry*> children;
	vector<JSONEntry*> array;
	Byte type;
	string text;

public:
	static const Byte OBJ = 0;
	static const Byte ARRAY = 1;
	static const Byte TEXT = 2;

	inline JSONEntry() {
		type = OBJ;
	}

	inline JSONEntry(const Byte type) {
		this->type = type;
	}

	inline JSONEntry(const string& text) {
		type = TEXT;
		this->text = text;
	}

	~JSONEntry();

	void empty();

	inline map<std::string, JSONEntry*>& getChildren() {
		return children;
	}

	inline vector<JSONEntry*>& getArray() {
		return array;
	}

	inline string& getText() {
		return text;
	}

	inline void setText(const string& text) {
		this->text = text;
	}

	inline Byte getType() {
		return type;
	}

	inline void setType(const Byte type) {
		this->type = type;
	}

	inline void add(const string& name, JSONEntry* e) {
		children.insert(map < string, JSONEntry* >::value_type(name, e));
	}

	inline void add(const string& name, const string& str) {
		JSONEntry* e = new JSONEntry(str);
		children.insert(map < string, JSONEntry* >::value_type(name, e));
	}

	JSONEntry* get(const string& name);

	bool dump(string &res);
};

#endif
