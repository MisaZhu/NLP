#include "StringUtils.hh"
#include "UTF8StringReader.hh"

void StringUtils::split(const string& s, vector<string>& ret, char stop, bool trm) {
  UTF8StringReader strReader;
	strReader.setString(s);

	ret.clear();

	std::string tmp;
	while(true) {
		Byte b = strReader.read();
		if(b == 0) {
			break;
		}
		
		if(b == stop || 
				(stop == 0 && 
					(b == ' ' ||
					b == '\t' ||
					b == '\r' ||
					b == '\n'))) {
			if(stop != 0 || tmp.length() > 0) {
				if(trm)
					tmp = trim(tmp);
				ret.push_back(tmp);
			}

			tmp = "";
			continue;
		}

		tmp.append(1, b);
	}

	if(stop != 0 || tmp.length() > 0) {
		if(trm)
			tmp = trim(tmp);
		ret.push_back(tmp);
	}
}

string StringUtils::trim(const string& s) {
	string ret = trimLeft(s);
	return trimRight(ret);
}

string StringUtils::trimLeft(const string& s) {
	size_t l = s.length();

	for(int i=0; i<l; ++i) {
		char b = s.at(i);
		if(b == ' ' ||
				b == '\t' ||
				b == '\r' ||
				b == '\n') {
			continue;
		}

		return s.substr(i);
	}

	return "";
}

string StringUtils::trimRight(const string& s) {

	for(int i=s.length()-1; i>=0; --i) {
		char b = s.at(i);
		if(b == ' ' ||
				b == '\t' ||
				b == '\r' ||
				b == '\n') {
			continue;
		}

		return s.substr(0, i+1);
	}

	return "";
}

