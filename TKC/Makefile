READER = ../Reader
UTILS = ../utils
SRCS = test.cc ${READER}/*.cc

CFLAGS = -I${UTILS} -I${READER}

all:
	g++ -g -o test ${CFLAGS} ${SRCS}

clean:
	rm -fr test *.o *.dSYM
