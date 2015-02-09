LIBSRCS = Reader.cc StdByteReader.cc UTF8Reader.cc

all:
	g++ -g -o test test.cc ${LIBSRCS}

clean:
	rm -fr test *.o
