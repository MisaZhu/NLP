#include "KNote.hh"

using namespace std;

void KNote::link(UInt to, bool up, UInt count) {
	map<UInt, UInt> *link;
	map<UInt, UInt>::iterator it;

	link = up ? (&linkUp) : (&linkDown);
	it = link->find(to);

	if(it == link->end()) { // new link
		link->insert(map <UInt, UInt>::value_type(to, count));
	} else {
		it->second += count;
	}
}

bool KNote::read(const string& str, KNote& note) {
	char c;
	int len = str.length();

	string s;
	UInt id, count;
	bool up = true;

	for(int i=0; i<len; ++i) {
		c = str[i];

		if(c == ']') { // end links 
			count = 0;
			if(s.length() != 0)
				count = std::stol(s);

			s = "";

			if(up) {
				if(count > 0)
					note.link(id, true, count);
				up = false; 
			}
			else {
				if(count > 0)
					note.link(id, false, count);
				return true; //finised.
			}
		} else if(c == '[') { // begin links
			continue;
		} else if(c == ',') { 
			count = std::stol(s);
			s = "";
			note.link(id, up, count);
		} else if(c == ':') { // begin links
			id = std::stol(s);
			s = "";
		} else {
			s += c;
		}
	}
	return false;
}


string KNote::dump(KNote& note) {
	stringstream ss;
	ss << "[";

	map<UInt, UInt>::iterator it;
	for(it=note.linkUp.begin(); it != note.linkUp.end(); it++) {
		if(it != note.linkUp.begin())
			ss << ",";
		ss << it->first << ":" << it->second;
	}
	ss << "][";

	for(it=note.linkDown.begin(); it != note.linkDown.end(); it++) {
		if(it != note.linkDown.begin())
			ss << ",";
		ss << it->first << ":" << it->second;
	}
	ss << "]";

	return ss.str();
} 

