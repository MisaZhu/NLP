KVDB = ../../KVDB
UNQLITE = ../../unqlite

SRCS = ${UNQLITE}/*.c ${KVDB}/*.cc test.cc
CFLAGS = -I${UNQLITE} -I${KVDB} -I../../utils 

all:
	g++ -g -o test ${CFLAGS} ${SRCS}

clean:
	rm -fr test *.o *.dSYM
