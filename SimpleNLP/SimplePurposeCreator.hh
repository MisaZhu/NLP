#ifndef SIMPLE_PURPOSEC_HH
#define SIMPLE_PURPOSEC_HH

#include <map>
#include "PIENlp.hh"
#include "UTF8Reader.hh"
#include "UTF8StringReader.hh"
#include "TinyJSON.hh"
#include "Indexer.hh"


using namespace std;

class StdReader : public NLPReader {
  UTF8Reader reader;
	StreamByteReader byteReader;
	
public:
	StdReader() {
		byteReader.setInputStream((std::istream*)&std::cin);
		reader.setByteReader((ByteReader*) &byteReader);
	}

	Input* read() {
		Input* in = NULL;

		string s = reader.readTill('\n');
		reader.read();
			
		if(s.length() == 0)
			return NULL;

		return new Input(s);
	}
};

class SimplePurposeCreator : public PurposeCreator {
	JSONEntry* json;
	map<size_t, JSONEntry*> purposeMap;
	Indexer keywordIndexer;

	void buildKeywordIndex(size_t id, string keywords); 

	bool buildIndex();

	Purpose* newPurpose(PIENlp* nlp, JSONEntry* purposeJson);

	JSONEntry* getPurposeJSON(size_t id); 

public:
	Purpose* newPurpose(PIENlp* nlp, Input* input);

	Purpose* newPurpose(PIENlp* nlp, size_t id);

	size_t getPurposeID(PIENlp* nlp, Input* input);

	bool loadConfig(const string& fname);
};

#endif

