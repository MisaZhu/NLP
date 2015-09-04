#include "Indexer.hh"

using namespace std;

int main(int argc, char** argv) {
	Indexer indexer;

	indexer.insert("abc", 0);
	indexer.insert("abc", 1);
	indexer.insert("abc", 0);
	indexer.insert("abc", 2);
	indexer.insert("abc", 3);

	indexer.insert("efg", 0);
	indexer.insert("efg", 3);

	indexer.insert("xxxx", 2);
	indexer.insert("xxxx", 3);

	vector<IDFreq> ret;
	vector<string> keys;

	keys.push_back("abc");
	keys.push_back("efg");
	keys.push_back("xxxx");

	indexer.search(keys, ret);
	indexer.search(keys, ret, false);

	return 0;
}


