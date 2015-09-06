#include <iostream>
#include "SimplePurpose.hh"
#include "StringUtils.hh"

bool SimplePurpose::keepInStack() {
	return inStack;
}

void SimplePurpose::talk(const string& text) {
	if(text.length() == 0)
		return;

	std::cout << "Purpose[" << name << "]: " << text <<"\n";
}

void SimplePurpose::dumpInputs() {
	string s;
	for(map<std::string, MyInput>::iterator it = inputs.begin(); it != inputs.end(); ++it) {
		string name = it->first;
		string value = it->second.value;

		s = s + "\t" + name + ": [" + value + "]\n";
	}
	std::cout << "Purpose[" << name << "]: {\n" << s <<"}\n\n";
}

void SimplePurpose::suspend() {
	inputExpected = "_suspend_";
	moreInput();
}
	
void SimplePurpose::resume() {
	inputExpected = "_resume_";
	moreInput();
}

bool SimplePurpose::fetchInput(const string& name, const string& input, string& value) {
	string::size_type pos = input.find(name + "(");

	if(pos != string::npos) { //found $name(
		string s = input.substr(pos + name.length() + 1);
		pos = s.find(")");
		if(pos != string::npos) { //found )
			s = s.substr(0, pos);
			value = s;
			return true;
		}
	}
	return false;
}

bool SimplePurpose::checkInput(Input* input) {
	string in = input->getText();
	bool ret = false;
	
	for(map<std::string, MyInput>::iterator it = inputs.begin(); it != inputs.end(); ++it) {
		string name = it->first;
		string value;

		if(fetchInput(name, in, value)) {
			it->second.value = value;
			ret = true;
		}
	}

	if(ret)
		inputExpected = "";
	dumpInputs();
	return ret;
}

void SimplePurpose::moreInput() {
	map<std::string, MyInput>::iterator it;

	if(inputExpected.length() != 0) {
		it = inputs.find(inputExpected);
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
				if(inputExpected.length() == 0)
					inputExpected = in;
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

	JSONEntry* js = purposeJSON->getChild("inputs");
	if(js != NULL) {

		JSONEntry* j;
		//loading the inputs requirement
		j = js->getChild("inputs");
		if(j != NULL) {
			for(map<std::string, JSONEntry*>::iterator it = j->children.begin(); it != j->children.end(); ++it) {
				MyInput in;
				string name = it->first;
				in.ask = it->second->text;

				inputs.insert(map<string, MyInput>::value_type(name, in));
			}
		}
		
		//loading the ready need
		j = js->getChild("ready");
		if(j != NULL) {
			string s = j->text;		
			StringUtils::split(s, readyCond, '|', true);
		}
	}

	js = purposeJSON->getChild("stack");
	if(js != NULL) {
		if(js->text == "yes" || js->text == "true")
			inStack = true;
	}
	return true;
}
