#include "MKNDict.hh"

void MKNDict::add(const MKN& mkn) {
	pair<map<string, MKN>::iterator, bool> res =
			dictByLabel.insert(map<string, MKN>::value_type(mkn.label, mkn));

	MKN* m = &res.first->second;
	dictByID.insert(map<UInt, MKN*>::value_type(mkn.id, m));
}

bool MKNDict::get(const string& label, MKN& mkn) {
	map<string, MKN>::iterator it = dictByLabel.find(label);
	if(it == dictByLabel.end())
		return false;

	mkn = it->second;
	return true;
}

bool MKNDict::get(const UInt id, MKN& mkn) {
	map<UInt, MKN*>::iterator it = dictByID.find(id);
	if(it == dictByID.end())
		return false;

	mkn = *(it->second);
	return true;
}
