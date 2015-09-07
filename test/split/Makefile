FRISO = ../../friso/src
SRCS = test.cc ${FRISO}/friso*.c

CFLAGS = -I../../utils -I${FRISO}

all:
	g++ -g -o test ${CFLAGS} ${SRCS}

clean:
	rm -fr test *.o *.dSYM
