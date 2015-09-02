READER = ../../reader/Reader.cc ../../reader/UTF8Reader.cc ../../reader/StreamByteReader.cc
JSON = ../../TinyJSON/*.cc
SRCS = test.cc ${UNQLITE} ${READER} ${JSON}

CFLAGS = -I../../TinyJSON -I../../utils -I../../reader
TARGET = jsontest

all:
	g++ -g -o ${TARGET} ${CFLAGS} ${SRCS}

clean:
	rm -fr ${TARGET} *.o *.dSYM
