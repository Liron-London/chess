/*
 * setting_test.c
 *
 *  Created on: Aug 12, 2017
 *      Author: Gal
 */

#include "setting.h"
#include <stdbool.h>

// TODO -- need to write
bool basic_check(){
	Command command = parse_line("start");
	if (command.validArg == false){
		printf("problem with start");
		return false;
	}

	Command command = parse_line("quit");
	if (command.validArg == false){
		printf("problem with quit");
		return false;
	}

	// checks game mode
	Command command = parse_line("game_mode 1");
	if (command.validArg == false || command.arg != 1){
		printf("problem with start");
		return false;
	}

	// checks user color
	Command command = parse_line("user_color 1");
	if (command.validArg == false || command.arg != 1){
		printf("problem with user_color");
		return false;
	}

	// checks user_color argument
	Command command = parse_line("user_color 3");
	if (command.validArg == true){
		printf("problem with user_color");
		return false;
	}

	return true;
}


int main() {
	bool success;
	success = basic_check();
	if (success)
		printf("basic settings checks success!\n"); //DEBUG
	return 0;
}
