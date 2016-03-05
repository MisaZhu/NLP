#ifndef INDEXER_HH
#define INDEXER_HH

#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

class IndexerItem  {
public:
	map<size_t, size_t> idMap;

	void insert(size_t id, size_t freq = 1);
};	

class IDFreq {
public:
	size_t id;
	size_t freq;
};
		
class Indexer {
	map<string, IndexerItem> itemMap;

	IndexerItem* search(const string& key);

	static IndexerItem* doAnd(const IndexerItem* item0, const IndexerItem* item1);

	static IndexerItem* doOr(const IndexerItem* item0, const IndexerItem* item1);

	static void sort(const IndexerItem* item, vector<IDFreq>& ret);

public:

	void insert(const string& key, size_t id);

	void search(const vector<string>& keys, vector<IDFreq>& ret, bool isAnd = true);
};


#endif
