#ifndef UNQLITE_CURSOR_HH
#define UNQLITE_CURSOR_HH

#include "utils.hh"
#include "KVCursor.hh"

extern "C" {
#include "unqlite.h"
}

class UnqliteCursor {
	unqlite_kv_cursor* cursor;	
public:
	void set(unqlite_kv_cursor* cs) {
		cursor = cs;
	}

	unqlite_kv_cursor* get() {
		return cursor;
	}

	virtual bool key(void* key, UInt* keyLen);

	virtual bool data(void* data, UInt* dataLen);

	virtual bool seek(const void* key, UInt keyLen, UInt pos);

	virtual bool next();

	virtual bool prev();

	virtual bool last();

	virtual bool first();

	virtual bool remove();
};

#endif
