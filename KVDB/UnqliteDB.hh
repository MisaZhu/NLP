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
	
	virtual bool fetch(const void* key, const UInt keyLen, void* value, UInt* valueLen);

	virtual bool store(const void* key, const UInt keyLen, const void* value, const UInt valueLen);

	virtual bool remove(const void* key, const UInt keyLen);
};

#endif
