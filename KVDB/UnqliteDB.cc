#include "UnqliteDB.hh"
#include "UnqliteCursor.hh"

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
	
bool UnqliteDB::fetch(const void* key, UInt keyLen, void* data, UInt* dataLen) {
	if(db == NULL || key == NULL || dataLen == NULL)
		return false;
	unqlite_int64 len;
	int r = unqlite_kv_fetch(db, (void*)key, keyLen, data, &len);
	if(r != UNQLITE_OK)
		return false;

	*dataLen = len;
	return true;
}

bool UnqliteDB::store(const void* key, UInt keyLen, const void* data, UInt dataLen) {
	if(db == NULL || key == NULL || data == NULL)
		return false;

	int r = unqlite_kv_store(db, (void*)key, keyLen, (void*)data, dataLen);
	if(r != UNQLITE_OK)
		return false;
	return true;
}


bool UnqliteDB::append(const void* key, UInt keyLen, const void* data, UInt dataLen) {
	if(db == NULL || key == NULL || data == NULL)
		return false;

	int r = unqlite_kv_append(db, (void*)key, keyLen, (void*)data, dataLen);
	if(r != UNQLITE_OK)
		return false;
	return true;
}

bool UnqliteDB::remove(const void* key, UInt keyLen) {
	if(db == NULL || key == NULL)
		return false;

	int r = unqlite_kv_delete(db, (void*)key, keyLen);
	if(r != UNQLITE_OK)
		return false;
	return true;
}

KVCursor* UnqliteDB::initCursor() {
	unqlite_kv_cursor* cursor = NULL;

	if(db == NULL)
		return NULL;

	int r = unqlite_kv_cursor_init(db, &cursor);
	if(r != UNQLITE_OK || cursor == NULL)
		return NULL;

	UnqliteCursor *ret = new UnqliteCursor();
	ret->set(cursor);
	return (KVCursor*)ret;
}

bool UnqliteDB::releaseCursor(KVCursor* cursor) {
	UnqliteCursor *c = (UnqliteCursor*)cursor;
	if(c == NULL || db == NULL)
		return false;

	unqlite_kv_cursor_release(db, c->get());
	delete cursor;
	return true;
}
