#include "StdByteReader.hh"

#include <iostream>

Byte StdByteReader::read() {
  int b;
	b = getchar();

	if(b <= 0)
		return 0;

	return (Byte)b;
}
