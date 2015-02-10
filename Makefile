SRCS = test.cc unqlite/unqlite.c Reader.cc UTF8Reader.cc StreamByteReader.cc

CFLAGS = -I./unqlite

all:
	g++ -g -o test ${CFLAGS} ${SRCS}

clean:
	rm -fr test *.o
