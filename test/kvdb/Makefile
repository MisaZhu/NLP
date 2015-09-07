READER = ../../reader/Reader.cc ../../reader/UTF8Reader.cc ../../reader/StreamByteReader.cc
UNQLITE = ../../unqlite/unqlite.c 
SRCS = test.cc ${UNQLITE} ${READER}

CFLAGS = -I../../unqlite -I../../utils -I../../reader

all:
	g++ -g -o test ${CFLAGS} ${SRCS}

clean:
	rm -fr test *.o *.dSYM
