#ifndef FRISO_SPLIT_HH
#define FRISO_SPLIT_HH

#include <string>
#include <vector>

#include "friso.h"
#include "friso_API.h"

using namespace std;

struct WordInfo {
	string word;
	int type;
};

class FrisoSplit {
	friso_t friso;
	friso_config_t config;
	
public:
	FrisoSplit() {
		friso = NULL;
		config = NULL;
	}

	~FrisoSplit() {
		if(config != NULL) {
			friso_free_config(config);
		}
		if(friso != NULL) {
			friso_free(friso);
		}
	}

	FrisoSplit(const string& confFname) {
		loadConfig(confFname);
	}

	bool loadConfig(const string& fname);
		
	void split(const string& str, vector<WordInfo>& res);
};

#endif
