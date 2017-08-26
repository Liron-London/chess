/*
 * setting_test.c
 *
 *  Created on: Aug 12, 2017
 *      Author: Gal
 */

#include "setting.h"
#include "game.h"
#include <stdbool.h>

// TODO -- need to expend
static bool basic_check(){
	game* game = game_create();
	Command* command = (Command*)malloc(sizeof(Command));

	// checking start
	command = parse_line(game, "start", command);
	if (command->validArg == false){
		printf("problem with start");
		return  false;
	}

	// checking quit
	command = parse_line(game, "quit", command);
	if (command->validArg == false){
		printf("problem with quit");
		return false;
	}

	// checks game mode
	command = parse_line(game, "game_mode 1", command);
	if (command->validArg == false || command->arg != 1){
		printf("problem with game mode");
		return false;
	}

	// checks user color
	command = parse_line(game, "user_color 1", command);
	if (command->validArg == false || command->arg != 1){
		printf("problem with user_color");
		return false;
	}

	// checks user_color argument
	command = parse_line(game, "user_color 3", command);
	if (command->validArg == true) {
		printf("problem with user_color");
		return false;
	}

	// checking difficulty
	command = parse_line(game, "difficulty 3", command);
	if (command->validArg == false || command->arg != 3){
		printf("problem with difficulty");
		return false;
	}

	command = parse_line(game, "difficulty 6", command);
	if (command->validArg == true){
		printf("problem with difficulty");
		return false;
	}

	print_settings(game);

	return true;
}


int main() {
	bool success;
	success = basic_check();
	if (success)
		printf("basic settings checks success!\n");
	return 0;
}
