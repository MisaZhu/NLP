#ifndef KVDB_HH
#define KVDB_HH

#include "utils.hh"
#include "KVCursor.hh"

class KVDB {
public:
	virtual bool open(const char* fname, bool wr) = 0;

	virtual bool close() = 0;
	
	virtual bool fetch(const void* key, UInt keyLen, void* data, UInt* dataLen) = 0;

	virtual bool store(const void* key, UInt keyLen, const void* data, UInt dataLen) = 0;

	virtual bool append(const void* key, UInt keyLen, const void* data, UInt dataLen) = 0;

	virtual bool remove(const void* key, UInt keyLen) = 0;

	virtual KVCursor* initCursor() = 0; 

	virtual bool releaseCursor(KVCursor* cursor) = 0; 
};

#endif
