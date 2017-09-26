/*
 * main.c
 *
 *  Created on: Sep 13, 2017
 *      Author: liron
 */
#include "setting.h"
#include "GUI.h"

int main(int argc, char* argv[]) {
	if (argc == 1 || strcmp(argv[1], "-c") == 0) {
		set_game();
	} else if (strcmp(argv[1], "-g") == 0) {
		gui();
	} else {
		printf("Invalid flag, exiting.\n");
		return 1;
	}
	return 0;
}
