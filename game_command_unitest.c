/*
 * game_command_unitest.c
 *
 *  Created on: Aug 19, 2017
 *      Author: Gal
 */

#include "game_commands.h"
#include <stdbool.h>

static bool basic_check(){
	// game* game = game_create();
	// return true;
	Gamecommand* game_command;

	game_command = game_command_parse_line("move <2,A> to <3,B>");
	printf("%d\n", game_command->move->source->row);
	printf("%c\n", game_command->move->source->column);
	printf("%d\n", game_command->move->dest->row);
	printf("%c\n", game_command->move->dest->column);

	return true;
}

static bool game_play_check(){
	game* cur_game = game_create();
	game_play(cur_game);
	return true;
}

int main() {
	bool success;
	success = basic_check();
	printf("before last if\n");
	if (success)
		printf("basic game_commands checks success!\n");
	success = game_play_check();
	return 0;
}
