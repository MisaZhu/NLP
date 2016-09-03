#include "JSONEntry.hh"
#include "TinyJSON.hh"


void JSONEntry::empty() {
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
}

JSONEntry::~JSONEntry() {
	empty();
}

JSONEntry* JSONEntry::get(const string& name) {
	std::map<string, JSONEntry*>::iterator it = children.find(name);
	if(it == children.end())
		return NULL;

	return it->second;
}

bool JSONEntry::dump(string& ret) {
	ret = "";

	if(type == JSONEntry::OBJ) {
		ret += "{";

		for(std::map<string, JSONEntry*>::iterator c = children.begin(); c != children.end(); ++c) {
			if(c != children.begin())
					ret += ",";

			string name = c->first;
			ret = ret + "\"" + name + "\":";

			JSONEntry* e = c->second;
			if(e != NULL) {
				string s = "";
				if(!e->dump(s))
					return false;

				ret += s;
			}
		}
		ret += "}";
	}
	else if(type == JSONEntry::TEXT) {
		ret = ret + "\"" + text + "\"";
	}
	else if(type == JSONEntry::ARRAY) {
		ret += "[";

		for(std::vector<JSONEntry*>::iterator it = array.begin(); it != array.end(); ++it) {
			JSONEntry* e = *it;
			if(e != NULL) {
				string s = "";
				if(!e->dump(s))
					return false;

				if(it != array.begin())
					ret += ",";
				ret += s;
			}
		}
		ret += "]";
	}
	return true;
}
