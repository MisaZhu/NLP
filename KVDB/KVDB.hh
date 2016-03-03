#ifndef KVDB_HH
#define KVDB_HH

#include "utils.hh"

class KVDB {
public:
	virtual bool open(const char* fname, bool wr) = 0;

	virtual bool close() = 0;
	
	virtual bool fetch(const void* key, const UInt keyLen, void* value, UInt* valueLen) = 0;

	virtual bool store(const void* key, const UInt keyLen, const void* value, const UInt valueLen) = 0;

	virtual bool remove(const void* key, const UInt keyLen) = 0;
};

#endif
