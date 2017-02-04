#ifndef MKNDICT_HH
#define MKNDICT_HH

#include <string>
#include <map>

#include "MKN.hh"

using namespace std;


class MKNDict {
	map<string, MKN> dictByLabel;
	map<UInt, MKN*> dictByID;
public:
	void add(const MKN& mkn);

	bool get(const string& label, MKN& mkn);

	bool get(const UInt id, MKN& mkn);
};




#endif
