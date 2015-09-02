READER = ../../reader/Reader.cc ../../reader/UTF8Reader.cc ../../reader/StreamByteReader.cc
NLP = ../../NLP/*.cc
JSON = ../../TinyJSON/*.cc
;UNQLITE = ../../unqlite/unqlite.c 
SRCS = test.cc ${UNQLITE} ${READER} ${NLP} ${JSON}

CFLAGS = -I../../unqlite -I../../utils -I../../reader -I../../NLP -I../../TinyJSON
TARGET = nlptest

all:
	g++ -g -o ${TARGET} ${CFLAGS} ${SRCS}

clean:
	rm -fr ${TARGET} *.o *.dSYM
