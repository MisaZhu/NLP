#ifndef KDICT_HH
#define KDICT_HH

#include <string>
#include "utils.hh"
#include "UnqliteDB.hh"

using namespace std;

static string COUNT = "__COUNT__";

class KDict {
	UnqliteDB db;
	bool writable;
public:
	//add word , return ID of this word, or 0 if failed.
	UInt add(const string& word);

	//get word ID, return 0 if failed.
	UInt getID(const string& word);

	//get word , return "" if failed.
	string getWord(UInt id);

	//open dict
	bool open(const string& fname, bool wr = false);

	//close dict
	bool close();
};

#endif
