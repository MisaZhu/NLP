UTILS = ../utils
READER = ../Reader
INDEXER = ../Indexer
NLP = ../NLP
JSON = ../TinyJSON
SRCS = *.cc ${READER}/*.cc ${NLP}/*.cc ${JSON}/*.cc ${INDEXER}/*.cc ${UTILS}/*.cc

CFLAGS = -I${READER} -I${NLP} -I${JSON} -I${INDEXER} -I${UTILS}
TARGET = nlptest

all:
	g++ -g -o ${TARGET} ${CFLAGS} ${SRCS}

clean:
	rm -fr ${TARGET} *.o *.dSYM
