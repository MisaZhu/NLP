#include "UnqliteDB.hh"

bool UnqliteDB::open(const char* fname, bool wr) {
	int r;

	if(wr)
		r = unqlite_open(&db, fname, UNQLITE_OPEN_READWRITE | UNQLITE_OPEN_MMAP | UNQLITE_OPEN_CREATE);
	else
		r = unqlite_open(&db, fname, UNQLITE_OPEN_READONLY | UNQLITE_OPEN_MMAP);

	if(db == NULL || r != UNQLITE_OK) {
		db = NULL;
		return false;
	}
	return true;
}

bool UnqliteDB::close() {
	if(db == NULL)
		return false;
	
	int r = unqlite_close(db);

	if(UNQLITE_OK != r)
		return false;
	return true;
}
	
bool UnqliteDB::fetch(const void* key, const UInt keyLen, void* value, UInt* valueLen) {
	if(db == NULL || key == NULL || value == NULL)
		return false;
	unqlite_int64 len;
	int r = unqlite_kv_fetch(db, (void*)key, keyLen, value, &len);
	if(r != UNQLITE_OK)
		return false;

	*valueLen = len;
	return true;
}

bool UnqliteDB::store(const void* key, const UInt keyLen, const void* value, const UInt valueLen) {
	if(db == NULL || key == NULL || value == NULL)
		return false;

	int r = unqlite_kv_store(db, (void*)key, keyLen, (void*)value, valueLen);
	if(r != UNQLITE_OK)
		return false;
	return true;
}

bool UnqliteDB::remove(const void* key, const UInt keyLen) {
	if(db == NULL || key == NULL)
		return false;

	int r = unqlite_kv_delete(db, (void*)key, keyLen);
	if(r != UNQLITE_OK)
		return false;
	return true;
}
