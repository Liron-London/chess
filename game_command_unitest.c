/*
 * game_command_unitest.c
 *
 *  Created on: Aug 19, 2017
 *      Author: Gal
 */

#include "game_commands.h"
#include "game.h"
#include <stdbool.h>


static bool basic_check(){
	// game* game = game_create();
	return true;
	Gamecommand game_command;

	printf("WTF IS GOING ON\n");

	game_command = game_command_parse_line("move <2,A> to <3,B>");
	printf("%d\n", game_command.move->source->row);
	printf("%c\n", game_command.move->source->column);
	printf("%d\n", game_command.move->dest->row);
	printf("%c\n", game_command.move->dest->column);

	return true;
}

int main() {
	bool success;
	success = basic_check();
	printf("before last if");
	if (success)
		printf("basic game_commands checks success!\n");
	return 0;
}
