#include <iostream>

#include "FrisoSplit.hh"

extern "C" {
//read a line from a command line.
static fstring getLine( FILE *fp, fstring __dst ) 
{
	register int c;
	register fstring cs;

	cs = __dst;
	while ( ( c = getc( fp ) ) != EOF ) {
		if ( c == '\n' ) break;
		*cs++ = c; 
	}
	*cs = '\0';

	return ( c == EOF && cs == __dst ) ? NULL : __dst;
}

}


using namespace std;

int main(int argc, char** argv) {
	char line[1024+1] = {0};

	if(argc != 2) {
		printf("Usage: test [friso init file]\n");
		return 1;
	}

	FrisoSplit split;
	split.loadConfig(argv[1]);
	while ( 1 ) 
	{
		vector<WordInfo> words;
		getLine( stdin, line );

		split.split(line, words);

		int sz = words.size();
		for(int i=0; i<sz; ++i) {
			std::cout << "[" + words[i].word + "] ";
		}

		std::cout << "\n";
	}

	return 0;
}
