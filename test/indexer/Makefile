INDEXER= ../../Indexer
SRCS = *.cc ${INDEXER}/*.cc

CFLAGS =  -I../../utils -I${INDEXER}

all:
	g++ -g -o test ${CFLAGS} ${SRCS}

clean:
	rm -fr test *.o *.dSYM
