#ifndef UnqliteDB_HH
#define UnqliteDB_HH

#include "KVDB.hh"

extern "C" {
#include "unqlite.h"
}

class UnqliteDB : public KVDB {
	unqlite *db;
public:
	virtual bool open(const char* fname, bool wr = false);

	virtual bool close();
	
	virtual bool fetch(const void* key, UInt keyLen, void* data, UInt* dataLen);

	virtual bool store(const void* key, UInt keyLen, const void* data, UInt dataLen);

	virtual bool append(const void* key, UInt keyLen, const void* data, UInt dataLen);

	virtual bool remove(const void* key, UInt keyLen);

	virtual KVCursor* initCursor();

	virtual bool releaseCursor(KVCursor* cursor); 
};

#endif
