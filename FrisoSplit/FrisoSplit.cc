#include "FrisoSplit.hh"

bool FrisoSplit::loadConfig(const string& fname) {
	friso = friso_new();
	config = friso_new_config();

	if ( friso_init_from_ifile(friso, config, (fstring)fname.c_str()) != 1 ) {
		friso_free_config(config);
		friso_free(friso);
		return false;
	}

	return true;
}


void FrisoSplit::split(const string& str, vector<WordInfo>& res) {
	if(friso == NULL || config == NULL)
		return;

	friso_task_t task;
	task = friso_new_task();

	friso_set_text(task, (fstring)str.c_str());
	while ( ( config->next_token( friso, config, task ) ) != NULL ) {
		WordInfo wi;
		wi.word = task->token->word;
		wi.type = task->token->pos;
		res.push_back(wi);
	}
	friso_free_task( task );
}
