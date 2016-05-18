#ifndef KLINK_HH
#define KLINK_HH

#include <string>
#include "utils.hh"
#include "UnqliteDB.hh"
#include "KNote.hh"
#include "KDict.hh"

using namespace std;

class KLink {
	UnqliteDB db;
	bool writable;
public:
	//open link db
	bool open(const string& fname, bool wr = false);

	//close link db
	bool close();

	//link w1 up to w2
	bool link(KDict* dict, const string& w1, const string& w2);

	//get note of word
	bool getNote(UInt id, KNote& note);
};

#endif
