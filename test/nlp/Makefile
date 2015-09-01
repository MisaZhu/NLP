READER = ../../reader/Reader.cc ../../reader/UTF8Reader.cc ../../reader/StreamByteReader.cc
;UNQLITE = ../../unqlite/unqlite.c 
SRCS = Purpose.cc NLP.cc test.cc ${UNQLITE} ${READER}

CFLAGS = -I../../unqlite -I../../utils -I../../reader
TARGET = nlptest

all:
	g++ -g -o ${TARGET} ${CFLAGS} ${SRCS}

clean:
	rm -fr ${TARGET} *.o *.dSYM
