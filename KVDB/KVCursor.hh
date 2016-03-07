#ifndef KVCURSOR_HH
#define KVCURSOR_HH

class KVCursor {
public:
	virtual ~KVCursor() = 0;

	virtual bool key(void* key, UInt* keyLen) = 0;

	virtual bool data(void* data, UInt* dataLen) = 0;

	virtual bool seek(const void* key, UInt keyLen, UInt pos) = 0;

	virtual bool next() = 0;

	virtual bool prev() = 0;

	virtual bool last() = 0;

	virtual bool first() = 0;

	virtual bool remove() = 0;
};

#endif
