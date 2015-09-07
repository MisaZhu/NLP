#include <fstream>
#include <sstream>

#include "friso_API.h"
#include "friso.h"



using namespace std;

int main(int argc, char** argv) {
	friso_t friso;
	friso_config_t config;
	friso_task_t task;


	//initialize
	friso = friso_new();
	config = friso_new_config();
	if ( friso_init_from_ifile(friso, config, argv[1]) != 1 ) {
		friso_free_config(config);
		friso_free(friso);
		return 1;
	}

	//set the task.
	task = friso_new_task();

	friso_set_text( task, "我们是否有什么问题");
	while ( ( config->next_token( friso, config, task ) ) != NULL ) {
		printf("%s ", task->token->word );
	}

	friso_free_task( task );

	friso_free_config(config);
	friso_free(friso);

	return 0;
}
