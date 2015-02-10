#include <fstream>

#include "UTF8Reader.hh"
#include "StreamByteReader.hh"

extern "C" {
#include "unqlite.h"
}


unsigned long registerWord(unqlite *db, const Byte* wp, unsigned int len) {
	unqlite_int64 sz;
	int rc;
	unsigned long count = 0;

	rc = unqlite_kv_fetch(db, (void*)wp, len, (void*)&count, &sz);
	if(rc != UNQLITE_OK) {
		count = 0;
	}
	
	count++;
	rc = unqlite_kv_store(db, wp, len, &count, sizeof(unsigned long));
	if(rc != UNQLITE_OK)
		count = 0;

	return count;
}

unsigned long getWordCount(unqlite *db, const Byte* wp, unsigned int len) {
	unqlite_int64 sz;
	int rc;
	unsigned long count = 0;

	rc = unqlite_kv_fetch(db, (void*)wp, len, (void*)&count, &sz);
	if(rc != UNQLITE_OK)
		count = 0;
	
	return count;
}

void setWordCount(unqlite *db, Byte* wp, size_t len, unsigned long count) {
	unqlite_kv_store(db, wp, len, &count, sizeof(unsigned long));
}

void training() {

  UTF8Reader reader;
	StreamByteReader byteReader;
	int rc;
	unqlite *db;

	rc = unqlite_open(&db,"wordPair.db", UNQLITE_OPEN_CREATE);
	if( rc != UNQLITE_OK ) { 
		std::cout << "Word pair database open failed!\n";
		return;
	}



	byteReader.setInputStream((std::istream*)&std::cin);

/*	std::ifstream is("data/all.txt", std::ifstream::binary);

	if(is) {
		byteReader.setInputStream((std::istream*)&is);
	}
	*/

	reader.setByteReader((ByteReader*) &byteReader);

	int len;
	bool ascii;


	Byte word[4], wordPair[7];

	word[0] = 0;
	word[3] = 0;
	wordPair[0] = 0;
	wordPair[6] = 0;

	unsigned long lines = 0;
	unsigned long max = 0;

	while(true) {
		const Byte* sw = reader.readSingleWord(len, ascii);
		if(len == 0)
			break;

		if(ascii) {
			if(sw[0] == '\n') {
				word[0] = 0;
				wordPair[0] = 0;
				++lines;
				if((lines % 10000) == 0) {
					std::cout << (lines*100.0/29895846.0) << "%\n";
					std::cout.flush();
				}
			}
		}
		else {
			if(word[0] == 0) {
				memcpy(word, sw, 3);
			}
			else {
				memcpy(wordPair, word, 3);
				memcpy(word, sw, 3);
				memcpy(wordPair+3, sw, 3);
				unsigned long count = registerWord(db, wordPair, 6);
				if(count > max)
					max = count;

				if(count == 1) {//new word pair
					count = registerWord(db, wordPair, 3);
					if(count > max)
						max = count;

					count = registerWord(db, wordPair+3, 3);
					if(count > max)
						max = count;
				}
			}
		}
	}

	memcpy(wordPair, "_WPMAX", 6);
	setWordCount(db, wordPair, 6, max);

	unqlite_close(db);
}

void split() {

	UTF8Reader reader;
	StreamByteReader byteReader;
	int rc;
	unqlite *db;

	std::cout << "Opening Word pair database ....\n";
	rc = unqlite_open(&db,"data/wordPair.db", UNQLITE_OPEN_READONLY | UNQLITE_OPEN_MMAP);
	if( rc != UNQLITE_OK ) { 
		std::cout << "Database open failed!\n";
		return;
	}

	unsigned long wpMax = getWordCount(db, (const Byte*)"_WPMAX", 6);
	std::cout << "Database opened. WP_Max = " << wpMax << "\n";

	byteReader.setInputStream((std::istream*)&std::cin);
	reader.setByteReader((ByteReader*) &byteReader);

	int len;
	bool ascii;

	Byte word[4], wordPair[7];

	word[0] = 0;
	word[3] = 0;
	wordPair[0] = 0;
	wordPair[6] = 0;

	while(true) {

		const Byte* sw = reader.readSingleWord(len, ascii);
		if(len == 0)
			break;

		if(ascii) {
			if(sw[0] == '\n') {
				word[0] = 0;
				wordPair[0] = 0;
				std::cout << "\n";
			}
			else {
				std::cout << "[" << sw << "] ";
			}
		}
		else {
			unsigned long count = getWordCount(db, sw, 3);
			std::cout << "[" << sw << ":" << (count * 1.0) / wpMax << "] ";

			if(word[0] == 0) {
				memcpy(word, sw, 3);
			}
			else {
				memcpy(wordPair, word, 3);
				memcpy(word, sw, 3);
				memcpy(wordPair+3, sw, 3);

				count = getWordCount(db, wordPair, 6);
				std::cout << "[" << wordPair << ":" << (count * 10.0 / wpMax) << "] ";
			}
		}
	}

	unqlite_close(db);
}

int main(int argc, char** argv) {
	if(argc > 1) {
		if(argv[1][0] == 't') {
			training();
		}
		else if(argv[1][0] == 's') {
			split();
		}
	}
	else {
		std::cout << "Split mode.\n";
		split();
	}
}


