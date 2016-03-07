#include "UnqliteCursor.hh"

bool UnqliteCursor::key(void* key, UInt* keyLen) {
	if(cursor == NULL || key == NULL || keyLen == NULL)
		return false;

	int l;
	int r = unqlite_kv_cursor_key(cursor, key, &l);	
	if(r != UNQLITE_OK)
		return false;

	*keyLen = l;
	return true;
}

bool UnqliteCursor::data(void* data, UInt* dataLen) {
	if(cursor == NULL || data == NULL || dataLen == NULL)
		return false;

	unqlite_int64 l;
	int r = unqlite_kv_cursor_data(cursor, data, &l);	
	if(r != UNQLITE_OK)
		return false;

	*dataLen = l;
	return true;
}

bool UnqliteCursor::seek(const void *key, UInt keyLen, UInt pos) {
	if(cursor == NULL || key == NULL)
		return false;

	int r = unqlite_kv_cursor_seek(cursor, key, keyLen, pos);
	if(r != UNQLITE_OK)
		return false;

	return true;
}


bool UnqliteCursor::next() {
	if(cursor == NULL)
		return false;

	int r = unqlite_kv_cursor_next_entry(cursor);
	if(r != UNQLITE_OK)
	    return false;

	return true;
}

bool UnqliteCursor::prev() {
	if(cursor == NULL)
		return false;

	int r = unqlite_kv_cursor_prev_entry(cursor);
	if(r != UNQLITE_OK)
	    return false;
	return true;
}

bool UnqliteCursor::last() {
	if(cursor == NULL)
		return false;

	int r = unqlite_kv_cursor_last_entry(cursor);
	if(r != UNQLITE_OK)
	    return false;

	return true;
}

bool UnqliteCursor::first() {
	if(cursor == NULL)
		return false;

	int r = unqlite_kv_cursor_first_entry(cursor);
	if(r != UNQLITE_OK)
	    return false;

	return true;
}

bool UnqliteCursor::remove() {
	if(cursor == NULL)
		return false;

	int r = unqlite_kv_cursor_delete_entry(cursor);
	if(r != UNQLITE_OK)
	    return false;

	return true;
}
