UNQLITE = ../../unqlite
KVDB = ../../KVDB

SRCS = ${UNQLITE}/*.c ${KVDB}/*.cc test.cc KNote.cc KDict.cc KLink.cc
CFLAGS = -I${UNQLITE} -I${KVDB} -I../../utils 

all:
	g++ -g -o test ${CFLAGS} ${SRCS}

clean:
	rm -fr test *.o *.dSYM
