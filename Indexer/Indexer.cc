#include <algorithm>
#include "Indexer.hh"

using namespace std;

void IndexerItem::insert(size_t id, size_t freq) {
	map<size_t, size_t>::iterator it = idMap.find(id);	
	if(it == idMap.end()) {
		idMap.insert(map <size_t, size_t>::value_type(id, freq));
	}
	else {
		it->second += freq;
	}
}
		
void Indexer::insert(const string& key, size_t id) {
	map<string, IndexerItem>::iterator it = itemMap.find(key);	
	if(it == itemMap.end()) {
		IndexerItem item;
		item.insert(id);
		itemMap.insert(map <string, IndexerItem>::value_type(key, item));
	}
	else {
		it->second.insert(id);
	}
}

IndexerItem* Indexer::search(const string& key) {
	IndexerItem* ret = new IndexerItem();
	map<string, IndexerItem>::iterator it = itemMap.find(key);	

	if(it != itemMap.end()) {
		ret->idMap = it->second.idMap;
	}
	return ret;
}

IndexerItem* Indexer::doAnd(const IndexerItem* item0, const IndexerItem* item1) {
	IndexerItem* ret = new IndexerItem();

	if(item0 == 0 || item1 == 0)
		return ret;

	const IndexerItem *small, *big;

	if(item0->idMap.size() < item1->idMap.size()) {
		small = item0;
		big = item1;
	} else {
		big = item0;
		small = item1;
	}
	

	for(map<size_t, size_t>::const_iterator it = small->idMap.begin(); it != small->idMap.end(); ++it) {
		map<size_t, size_t>::const_iterator fnd = big->idMap.find(it->first);

		if(fnd != big->idMap.end()) {
			ret->insert(it->first, it->second + fnd->second);
		}
	}

	return ret;
}

IndexerItem* Indexer::doOr(const IndexerItem* item0, const IndexerItem* item1) {
	IndexerItem* ret = new IndexerItem();

	if(item1 != NULL)
		ret->idMap = item1->idMap;

	if(item0 != NULL) {
		for(map<size_t, size_t>::const_iterator it = item0->idMap.begin(); it != item0->idMap.end(); ++it) {
			ret->insert(it->first, it->second);
		}
	}
	return ret;
}

static bool _comp_(const IDFreq &a, const IDFreq &b) {
	return a.freq > b.freq;
}

void Indexer::sort(const IndexerItem* item, vector<IDFreq> & ret) {
	if(item == NULL)
		return;

	for(map<size_t, size_t>::const_iterator it = item->idMap.begin(); it != item->idMap.end(); ++it) {
		IDFreq idFreq;
		idFreq.id = it->first;
		idFreq.freq = it->second;

		ret.push_back(idFreq);
	}

	::sort(ret.begin(), ret.end(), _comp_);
}

void Indexer::search(const vector<string>& keys, vector<IDFreq>& ret, bool isAnd) {
	ret.clear();
	
	size_t num = keys.size();
	if(num == 0)
		return;

	IndexerItem *first = NULL;
	IndexerItem *second = NULL;
	IndexerItem *res = NULL;

	for(size_t i=0; i<num; ++i) {
		first = search(keys[i]);

		if(second == NULL) {
			second = first;
		} else {
			if(isAnd) 
				res = Indexer::doAnd(first, second);
			else
				res = Indexer::doOr(first, second);
			
			delete first;
			delete second;
			second = res;
		}
	}

	if(second != NULL) {
		Indexer::sort(second, ret);
		delete second;
	}
}
