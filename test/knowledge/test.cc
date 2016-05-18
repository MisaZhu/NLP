#include <iostream>
#include "KNote.hh"
#include "KDict.hh"
#include "KLink.hh"

using namespace std;

int main(int argc, char** argv) {
	KDict dict;
	KLink link;

	dict.open("dict.db", true);
	link.open("link.db", true);


	link.link(&dict, "test1", "test2");


	link.close();
	dict.close();

	return 0;
}
