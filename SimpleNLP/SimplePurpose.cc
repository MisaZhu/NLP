#include <iostream>
#include "SimplePurpose.hh"
#include "StringUtils.hh"

void SimplePurpose::talk(const string& text) {
	if(text.length() == 0)
		return;

	std::cout << "Purpose[" << name << "]: " << text <<"\n";
}

void SimplePurpose::suspend() {
  JSONEntry* j = purposeJSON->getChild("suspend");
	if(j == NULL)
		return;
	
	talk(j->text);
}
	
void SimplePurpose::resume() {
  JSONEntry* j = purposeJSON->getChild("resume");
	if(j == NULL)
		return;
	
	talk(j->text);
}

bool SimplePurpose::fetchInput(const string& name, const string& input, string& value) {
	string::size_type pos = input.find(name + "(");

	if(pos != string::npos) { //found $name(
		string s = input.substr(pos + name.length() + 1);
		pos = s.find(")");
		if(pos != string::npos) { //found )
			s = s.substr(0, pos);
			value = s;
			talk(name + " inputed with : " + value);
			return true;
		}
	}
	return false;
}

bool SimplePurpose::checkInput(Input* input) {
	string in = input->getText();
	
	for(map<std::string, MyInput>::iterator it = inputs.begin(); it != inputs.end(); ++it) {
		string name = it->first;
		string value;
		if(fetchInput(name, in, value)) {
			it->second.value = value;
			return true;
		}
	}

	return false;
}

void SimplePurpose::moreInput() {
	map<std::string, MyInput>::iterator it;
	if(tryInput.length() != 0) {
		it = inputs.find(tryInput);
		tryInput = "";

		if(it != inputs.end()) {
			if(it->second.value.length() == 0) {
				talk(it->second.ask);
				return;
			}
		}
	}

	for(it = inputs.begin(); it != inputs.end(); ++it) {
		if(it->second.value.length() == 0) {
			talk(it->second.ask);
			return;
		}
	}
}

bool SimplePurpose::checkReady(const string& cond) {
	if(cond == "*")
		return true;

	vector<string> conds;
	StringUtils::split(cond, conds, '&', true);
	int num = conds.size();
	for(int i=0; i<num; ++i) {
		string in = conds[i];
		if(in.length() != 0) {
			map<std::string, MyInput>::iterator it = inputs.find(in);
			if(it == inputs.end())
				return false;
			
			if(it->second.value.length() == 0) {
				if(tryInput.length() == 0)
					tryInput = in;
				return false;
			}
		}
	}

	return true;
}

bool SimplePurpose::ready() {
	int num = readyCond.size();
	for(int i=0; i<num; ++i) {
		string cond = readyCond[i];

		if(checkReady(cond)) {
			talk(cond + " ready.");
			return true;
		}
	}

	return false;
}	

Input* SimplePurpose::execute() {
	talk("execute!");
	return NULL;
}

bool SimplePurpose::init() {
	name = purposeJSON->name;

	JSONEntry* jInput = purposeJSON->getChild("inputs");
	if(jInput == NULL) 
		return false;

	JSONEntry* j;
	//loading the inputs requirement
	j = jInput->getChild("inputs");
	if(j != NULL) {
		for(map<std::string, JSONEntry*>::iterator it = j->children.begin(); it != j->children.end(); ++it) {
			MyInput in;
			string name = it->first;
			in.ask = it->second->text;

			inputs.insert(map<string, MyInput>::value_type(name, in));
		}
	}
	
	//loading the ready need
	j = jInput->getChild("ready");
	if(j != NULL) {
		string s = j->text;		
		StringUtils::split(s, readyCond, '|', true);
	}

	return true;
}
