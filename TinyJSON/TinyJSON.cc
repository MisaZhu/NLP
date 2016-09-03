#include "TinyJSON.hh"
#include "UTF8StringReader.hh"
#include <vector>
#include <stdio.h>

using namespace std;

bool TinyJSON::parse(JSONEntry& elm, const string& str) {
	UTF8StringReader r;
	r.setString(str);

	TinyJSON tinyJSON;
	tinyJSON.setReader(&r);
	return tinyJSON.parse(elm);
}

bool TinyJSON::parse(JSONEntry& elm) {
	elm.empty();
	return readElm(elm);
}

bool TinyJSON::readElm(JSONEntry& elm, Byte state) {
	if(reader == NULL)
		return false;

	int len;
	bool ascii;

	const Byte* sw;
	string name;

	elm.setType(JSONEntry::OBJ);

	while(true) {
		sw = reader->readSingleWord(len, ascii, true);
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
			JSONEntry *e = new JSONEntry();
			if(e == NULL)
				return false;

			if(sw[0] == '{') {
				e->setType(JSONEntry::OBJ);
				if(!readElm(*e, NAME)) {
					delete e;
					return false;
				}
				//elm.object = e;
				elm.add(name, e);
			}
			else if(sw[0] == '"') {
				sw = reader->readTill(len, '"');
				e->setText((const char*)sw);

				if(reader->read() != '"') {
					delete e;
					return false;
				}

				e->setType(JSONEntry::TEXT);
				elm.add(name, e);
			}
			else if(sw[0] == '[') {
					while(true) {
					JSONEntry *item = new JSONEntry();
					if(item == NULL || !readElm(*item)) {
						delete item;
						delete e;
						return false;
					}
					e->getArray().push_back(item);

					sw = reader->readSingleWord(len, ascii, true);
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
				e->setType(JSONEntry::ARRAY);
				elm.add(name, e);
			}
			else {
				delete e;
				return false;
			}

			sw = reader->readSingleWord(len, ascii, true);

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

			sw = reader->readSingleWord(len, ascii, true);
			if(len == 0 || sw[0] != ':') 
				return false;

			state = CONTENT;
		}
	}

	return true;
}

