FRISO = ../../friso/src
SPLIT = ../../FrisoSplit
SRCS = test.cc ${FRISO}/friso*.c ${SPLIT}/*.cc

CFLAGS = -I../../utils -I${FRISO} -I${SPLIT}

all:
	g++ -g -o test ${CFLAGS} ${SRCS}

clean:
	rm -fr test *.o *.dSYM
