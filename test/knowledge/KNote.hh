#ifndef KNOTE_HH
#define KNOTE_HH

#include <sstream>
#include <map>
#include "utils.hh"


using namespace std;

class KNote {
public:
	map<UInt, UInt> linkUp;
	map<UInt, UInt> linkDown;

	void link(UInt to, bool up, UInt count = 1);

public:
	static string dump(KNote& note);
	static bool read(const string& str, KNote& note);
}; 


#endif
