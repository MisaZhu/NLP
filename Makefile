LIBSRCS = Reader.cc StdByteReader.cc

all:
	g++ -g -o test test.cc ${LIBSRCS}

clean:
	rm -fr test *.o
