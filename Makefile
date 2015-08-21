SRCS = test.cc unqlite/unqlite.c reader/Reader.cc reader/UTF8Reader.cc reader/StreamByteReader.cc

CFLAGS = -I./unqlite -I./reader

all:
	g++ -g -o test ${CFLAGS} ${SRCS}

clean:
	rm -fr test *.o
