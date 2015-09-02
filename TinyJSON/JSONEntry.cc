#include "JSONEntry.hh"


JSONEntry::~JSONEntry() {
	for(std::vector<JSONEntry*>::iterator it = array.begin(); it != array.end(); ++it) {
		JSONEntry* e = *it;
		if(e != NULL)
			delete e;
	}

	for(std::map<string, JSONEntry*>::iterator it = children.begin(); it != children.end(); ++it) {
		JSONEntry* e = it->second;
		if(e != NULL)
			delete e;
	}

	if(object != NULL)
		delete object;
}

JSONEntry* JSONEntry::getChild(const string& name) {
	std::map<string, JSONEntry*>::iterator it = children.find(name);
	if(it == children.end())
		return NULL;

	return it->second;
}
