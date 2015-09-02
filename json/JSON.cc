#include "JSON.hh"

using namespace std;

JSONElm* JSON::parse() {
	JSONElm* ret = new JSONElm();
	if(ret == NULL)
		return NULL;

	if(readElm(*ret))
		return ret;

	delete ret;
	return NULL;
}

bool JSON::readElm(JSONElm& elm, Byte state) {
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
				if(e->object == NULL) {
					e->object = new JSONElm();
				}

				if(!readElm(*e->object, NAME)) {
					delete e;
					return false;
				}
				e->type = JSONElm::OBJ;
				elm.child.insert(map < string, JSONElm* >::value_type(name, e));
			}
			else if(sw[0] == '"') {
				sw = reader->readTill(len, '"');
				e->text = (const char*)sw;

				if(reader->read() != '"') {
					delete e;
					return false;
				}

				e->type = JSONElm::TEXT;
				elm.child.insert(map < string, JSONElm* >::value_type(name, e));
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
				elm.child.insert(map < string, JSONElm* >::value_type(name, e));
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
