#include "PurposeC.hh"
#include "MyPurpose.hh"
#include "StringUtils.hh"

using namespace std;


void PurposeC::buildKeywordIndex(size_t id, string keywords) {
	vector<string> keys;
	StringUtils::split(keywords, keys);
	int num = keys.size();

	for(int i=0; i<num; ++i) {
		keywordIndexer.insert(keys[i], id);
	}
}

bool PurposeC::buildIndex() {
	size_t index = 0;
	
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
					JSONEntry* keys = purpose->getChild("keywords");
					if(keys != NULL) {
						buildKeywordIndex(index, keys->text);
					}
					purposeMap.insert(map<size_t, JSONEntry*>::value_type(index, purpose));
					index++;
				}
			}
		}
	}
	return true;
}

Purpose* PurposeC::newPurpose(NLP* nlp, JSONEntry* purposeJson) {
	MyPurpose* ret = new MyPurpose(nlp, purposeJson);	
	if(!ret->init()) {
		delete ret;
		return NULL;
	}
	
	return ret;
}

JSONEntry* PurposeC::getPurposeJSON(size_t id) {
	map<size_t, JSONEntry*>::iterator it = purposeMap.find(id);
	if(it == purposeMap.end())
		return NULL;

	return it->second;
}

Purpose* PurposeC::newPurpose(NLP* nlp, Input* input) {
	vector<IDFreq> pIDs;
	vector<string> words;

	StringUtils::split(input->getText(), words);
	
	keywordIndexer.search(words, pIDs, false);
	if(pIDs.size() == 0)
		return NULL;

	JSONEntry* purposeJson = getPurposeJSON(pIDs[0].id);
	if(purposeJson == NULL)
		return NULL;

	Purpose* ret = newPurpose(nlp, purposeJson); 
	return ret;
}

bool PurposeC::loadConfig(const string& fname) {
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
