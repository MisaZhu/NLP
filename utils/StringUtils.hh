#ifndef STRUTILS_HH
#define STRUTILS_HH

#include <string>
#include <vector>

using namespace std;

class StringUtils {
public:
	static void split(const string& s, vector<string>& ret, char stop = 0, bool trm = false);

	static string trimLeft(const string& s);

	static string trimRight(const string& s);

	static string trim(const string& s);

};

#endif
