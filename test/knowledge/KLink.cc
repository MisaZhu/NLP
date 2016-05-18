#include "KLink.hh"

bool KLink::link(KDict * dict, const string& w1, const string& w2) {
	if(dict == NULL)
		return false;
	
	UInt id1 = dict->add(w1);
	UInt id2 = dict->add(w2);
	if(id1 == 0 || id2 == 0)
		return false;

	KNote note1;
	KNote note2;
	getNote(id1, note1);
	getNote(id2, note2);
	
	note1.link(id2, true); //link up
	note2.link(id1, false); //link down

	string s = KNote::dump(note1);
	UInt len = s.length();

	if(!db.store(&id1, (UInt)sizeof(UInt), s.c_str(), len))
		return false;

	s = KNote::dump(note2);
	len = s.length();
	if(!db.store(&id2, (UInt)sizeof(UInt), s.c_str(), len))
		return false;
	return true;
}


bool KLink::getNote(UInt id, KNote& note) {
	UInt len = 0;
	if(!db.fetch(&id, (UInt)sizeof(UInt), NULL, &len) || len == 0)
		return false;

	char *str = new char[len+1];
	if(str == NULL)
		return false;
	str[len] = 0;

	if(!db.fetch(&id, (UInt)sizeof(UInt), str, &len))
		return false;
	

	return KNote::read(str, note);
}

bool KLink::open(const string& fname, bool wr) {
	if(!db.open(fname.c_str(), wr)) {
		return false;
	}

	writable = wr;
	return true;
}

bool KLink::close() {
	return db.close();
}
