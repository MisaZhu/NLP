#include <iostream>

#include "Reader.hh"

int main(int argc, char** argv) {
  Reader reader;
	int len;
	const char* sw = reader.readSingleWord(len);

	std::cout << sw ;
	return 0;
}
