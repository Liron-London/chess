/*
 * game_command.c
 *
 *  Created on: Aug 19, 2017
 *      Author: Gal
 */
#include "game_commands.h"

Gamecommand game_command_parse_line(const char* str){
	char* str_copy = malloc(strlen(str) + 1);
	strcpy(str_copy, str);
	char* command_text = strtok(str_copy, " \t\n");
	location* source;
	location* target;

	Gamecommand game_command;
	game_command.validArg = false;


	// char* command_int = strtok(NULL, " \t\n");


	if (strcmp(command_text, "move") == true){
		// need to be checked
		game_command.cmd = MOVE;

		source->row = atoi(strtok(str_copy, "<,>"));
		source->column = strtok(str_copy, "<,>")[0];
		target->row = atoi(strtok(str_copy, "<,>"));
		target->column = strtok(str_copy, "<,>")[0];

		//TODO -- need to verify that locations are intialized well
		game_command.move->source = source;
		game_command.move->dest = target;
		game_command.validArg = true;

		return game_command;
	}

	if (strcmp(command_text, "quit") == true){
		game_command.cmd = GAME_QUIT;
		game_command.validArg = true;
		return game_command;
	}

	if (strcmp(command_text, "undo") == true){
		game_command.cmd = UNDO;
		game_command.validArg = true;
		return game_command;
	}

	if (strcmp(command_text, "reset") == true){
		game_command.cmd = RESET;
		game_command.validArg = true;
		return game_command;
	}

	if (strcmp(command_text, "reset") == true){
		game_command.cmd = RESET;
		game_command.validArg = true;
		return game_command;
	}

	if (strcmp(command_text, "save") == true){
		//need to complete saving mode
		game_command.cmd = SAVE;
		game_command.validArg = true;
		return game_command;
	}
	return game_command;
}




