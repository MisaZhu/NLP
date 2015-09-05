#include "PurposeC.hh"


int main(int argc, char** argv) {
	NLP nlp;
	StdReader reader;
	PurposeC pc;

	if(pc.loadConfig("conf.json")) {
		nlp.setReader(&reader);
		nlp.setPurposeCreator(&pc);
		nlp.run();
	}

	return 0;
}
