READER = ../../reader
SRCS = test.cc ${UNQLITE} ${READER}/*.cc

CFLAGS = -I../../utils -I${READER}

all:
	g++ -g -o test ${CFLAGS} ${SRCS}

clean:
	rm -fr test *.o *.dSYM
