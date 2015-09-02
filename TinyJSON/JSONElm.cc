#include "JSONElm.hh"


JSONElm::~JSONElm() {
	for(std::vector<JSONElm*>::iterator it = array.begin(); it != array.end(); ++it) {
		JSONElm* e = *it;
		if(e != NULL)
			delete e;
	}

	for(std::map<string, JSONElm*>::iterator it = child.begin(); it != child.end(); ++it) {
		JSONElm* e = it->second;
		if(e != NULL)
			delete e;
	}

	if(object != NULL)
		delete object;
}

