#include "SimplePurposeCreator.hh"
#include "SimplePurpose.hh"
#include "StringUtils.hh"

using namespace std;


void SimplePurposeCreator::buildKeywordIndex(size_t id, string keywords) {
	vector<string> keys;
	StringUtils::split(keywords, keys);
	int num = keys.size();

	for(int i=0; i<num; ++i) {
		keywordIndexer.insert(keys[i], id);
	}
}

bool SimplePurposeCreator::buildIndex() {
	size_t index = 1; // 0 preserved for default purpose.
	size_t pIndex;
	
	JSONEntry* purposes = json->getChild("purposes");

	if(purposes == NULL || purposes->type != JSONEntry::ARRAY) {
		return false;
	}
	
	for(vector<JSONEntry*>::iterator it = purposes->array.begin(); it != purposes->array.end(); ++it) {
		JSONEntry* item = *it;
		if(item != NULL) {
			map<string, JSONEntry*>::iterator pit = item->children.begin();
			if(pit != item->children.end()) {
				JSONEntry* purpose = pit->second;
				if(purpose != NULL) {
					pIndex = index;
					JSONEntry* keys = purpose->getChild("keywords");
					if(keys != NULL) {
						if(keys->text == "*")
							pIndex = 0; //defauilt purpose.
						else
							buildKeywordIndex(index, keys->text);
					}

					purposeMap.insert(map<size_t, JSONEntry*>::value_type(pIndex, purpose));
					if(pIndex != 0)
						index++;
				}
			}
		}
	}
	return true;
}

Purpose* SimplePurposeCreator::newPurpose(PIENlp* nlp, JSONEntry* purposeJson) {
	SimplePurpose* ret = new SimplePurpose(nlp, purposeJson);	
	if(!ret->init()) {
		delete ret;
		return NULL;
	}
	
	return ret;
}

JSONEntry* SimplePurposeCreator::getPurposeJSON(size_t id) {
	map<size_t, JSONEntry*>::iterator it = purposeMap.find(id);
	if(it == purposeMap.end())
		return NULL;

	return it->second;
}

size_t SimplePurposeCreator::getPurposeID(PIENlp* nlp, Input* input) {
	vector<IDFreq> pIDs;
	vector<string> words;

	StringUtils::split(input->getText(), words);
	
	keywordIndexer.search(words, pIDs, false);

	size_t id = 0; //default purpose.

	if(pIDs.size() != 0)
		id = pIDs[0].id;

	return id;
}

Purpose* SimplePurposeCreator::newPurpose(PIENlp* nlp, size_t id) {
	JSONEntry* purposeJson = getPurposeJSON(id);
	if(purposeJson == NULL)
		return NULL;

	Purpose* ret = newPurpose(nlp, purposeJson); 
	ret->setID(id);
	return ret;
}

Purpose* SimplePurposeCreator::newPurpose(PIENlp* nlp, Input* input) {
	size_t id = getPurposeID(nlp, input);
	return newPurpose(nlp, id);
}

bool SimplePurposeCreator::loadConfig(const string& fname) {
	UTF8Reader reader;
	StreamByteReader byteReader;
	std::filebuf fb;
	if (!fb.open (fname, std::ios::in)) {
		return false;
	}

	std::istream is(&fb);  
	byteReader.setInputStream((std::istream*)&is);
	reader.setByteReader((ByteReader*) &byteReader);

	TinyJSON tj;
	tj.setReader(&reader);

	json = tj.parse();
	fb.close();

	if(json == NULL)
		return false;

	return buildIndex();
}
