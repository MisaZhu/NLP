LIBSRCS = Reader.cc 

all:
	g++ -g -o test test.cc ${LIBSRCS}

clear:
	rm -fr test *.o
