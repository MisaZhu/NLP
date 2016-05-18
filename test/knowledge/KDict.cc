#include "KDict.hh"

UInt KDict::add(const string& word) {
	UInt id = getID(word);
	if(id > 0)
		return id;

	if(!writable) //can not be wrote
		return 0;

	id = getID(COUNT);
	id++;

	if(!db.store(COUNT.c_str(), COUNT.length(), &id, (UInt)sizeof(UInt)))
		return 0;
	
	if(!db.store(word.c_str(), word.length(), &id, (UInt)sizeof(UInt)))
		return 0;

	if(!db.store(&id, (UInt)sizeof(UInt), word.c_str(), word.length()))
		return 0;

	return id;
}

string KDict::getWord(UInt id) {
	UInt len = 0;
	if(!db.fetch(&id, (UInt)sizeof(UInt), NULL, &len) || len == 0)
		return "";

	char *str = new char[len+1];
	if(str == NULL)
		return "";
	str[len] = 0;

	if(!db.fetch(&id, (UInt)sizeof(UInt), str, &len))
		return "";
	return str;
}

UInt KDict::getID(const string& word) {
	UInt id;
	UInt len;
	if(db.fetch(word.c_str(), word.length(), &id, &len))
		return id;

	return 0;
}

bool KDict::open(const string& fname, bool wr) {
	if(!db.open(fname.c_str(), wr)) {
		return false;
	}

	writable = wr;
	return true;
}

bool KDict::close() {
	return db.close();
}
