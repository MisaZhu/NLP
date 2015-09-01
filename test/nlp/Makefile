READER = ../../reader/Reader.cc ../../reader/UTF8Reader.cc ../../reader/StreamByteReader.cc
NLP = ../../NLP/*.cc
;UNQLITE = ../../unqlite/unqlite.c 
SRCS = test.cc ${UNQLITE} ${READER} ${NLP}

CFLAGS = -I../../unqlite -I../../utils -I../../reader -I../../NLP
TARGET = nlptest

all:
	g++ -g -o ${TARGET} ${CFLAGS} ${SRCS}

clean:
	rm -fr ${TARGET} *.o *.dSYM
