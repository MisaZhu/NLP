#include "SimplePurposeCreator.hh"


int main(int argc, char** argv) {
	PIENlp nlp;
	StdReader reader;
	SimplePurposeCreator pc;

	if(pc.loadConfig("conf.json")) {
		nlp.setReader(&reader);
		nlp.setPurposeCreator(&pc);
		nlp.run();
	}

	return 0;
}
