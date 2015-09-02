#include "TinyJSON.hh"
#include <vector>
#include <stdio.h>

using namespace std;

JSONElm* TinyJSON::parse() {
	JSONElm* ret = new JSONElm();
	if(ret == NULL)
		return NULL;

	if(readElm(*ret))
		return ret;

	delete ret;
	return NULL;
}

bool TinyJSON::readElm(JSONElm& elm, Byte state) {
	if(reader == NULL)
		return false;

	int len;
	bool ascii;

	const Byte* sw;
	string name;

	elm.type = JSONElm::OBJ;

	while(true) {
		sw = reader->readSingleWord(len, ascii);
		if(len == 0)
			break;

		if(state == ELM) {
			if(sw[0] != '{')
				return false;
			else  {
				state = NAME;
				continue;
			}
		}
		
		if(state == CONTENT) {
			JSONElm *e = new JSONElm();
			if(e == NULL)
				return false;
			e->name = name;

			if(sw[0] == '{') {
				e->type = JSONElm::OBJ;
				if(!readElm(*e, NAME)) {
					delete e;
					return false;
				}
				//elm.object = e;
				elm.children.insert(map < string, JSONElm* >::value_type(name, e));
			}
			else if(sw[0] == '"') {
				sw = reader->readTill(len, '"');
				e->text = (const char*)sw;

				if(reader->read() != '"') {
					delete e;
					return false;
				}

				e->type = JSONElm::TEXT;
				elm.children.insert(map < string, JSONElm* >::value_type(name, e));
			}
			else if(sw[0] == '[') {
					while(true) {
					JSONElm *item = new JSONElm();
					if(item == NULL || !readElm(*item)) {
						delete item;
						delete e;
						return false;
					}
					e->array.push_back(item);

					sw = reader->readSingleWord(len, ascii);
					if(len == 0) {
						delete e;
						return false;
					}	

					if(sw[0] == ']')
						break;

					if(sw[0] != ',') {
						delete e;
						return false;
					}
				}
				e->type = JSONElm::ARRAY;
				elm.children.insert(map < string, JSONElm* >::value_type(name, e));
			}
			else {
				delete e;
				return false;
			}

			sw = reader->readSingleWord(len, ascii);

			if(len == 0) {
				return false;
			}

			if(sw[0] == '}')
				break;

			if(sw[0] != ',') {
				return false;
			}
		
			state = NAME;
			continue;
		}

		if(state == NAME) { //read name
			if(sw[0] != '"')
				return false;
			sw = reader->readTill(len, '"');
			if(len == 0 || reader->read() != '"') 
				return false;

			name = (const char*)sw;

			sw = reader->readSingleWord(len, ascii);
			if(len == 0 || sw[0] != ':') 
				return false;

			state = CONTENT;
		}
	}

	return true;
}

bool TinyJSON::dump(JSONElm& elm, string& ret) {
	ret = "";

	if(elm.name.length() > 0)
		ret = ret + "\"" + elm.name + "\":";


	if(elm.type == JSONElm::OBJ)
		ret += "{";

	if(elm.type == JSONElm::TEXT) {
		ret = ret + "\"" + elm.text + "\"";
	}
	else if(elm.type == JSONElm::OBJ) {
		string s;

		if(elm.object != NULL) {
			if(!dump(*elm.object, s))
				return false;
			else {
				ret += s;
			}
		}
	}
	else if(elm.type == JSONElm::ARRAY) {
		ret += "[";

		for(std::vector<JSONElm*>::iterator it = elm.array.begin(); it != elm.array.end(); ++it) {
			JSONElm* e = *it;
			if(e != NULL) {
				string s = "";
				if(!dump(*e, s))
					return false;

				if(it != elm.array.begin())
					ret += ",";
				ret += s;
			}
		}
		ret += "]";
	}

	for(std::map<string, JSONElm*>::iterator c = elm.children.begin(); c != elm.children.end(); ++c) {
		JSONElm* e = c->second;
		if(e != NULL) {
			string s = "";
			if(!dump(*e, s))
				return false;

			if(c != elm.children.begin())
				ret += ",";
			ret += s;
		}
	}

	if(elm.type == JSONElm::OBJ)
		ret += "}";
	return true;
}
