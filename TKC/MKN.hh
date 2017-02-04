#ifndef MKN_HH
#define MKN_HH

#include <string>
#include <map>

#include "utils.hh"

using namespace std;

typedef struct MetaKnowledgeNode {
	UInt id;
	string label;

	bool isLink;
	bool compressable;

	MetaKnowledgeNode() {
		id = 0;
		isLink = false;
		compressable = false;
	}
} MKN;


#endif
