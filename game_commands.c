/*
 * game_command.c
 *
 *  Created on: Aug 19, 2017
 *      Author: Gal
 */
#include "game_commands.h"

Gamecommand game_command_parse_line(const char* str){
	printf("In the function\n");

	char* str_copy = malloc(strlen(str) + 1);
	strcpy(str_copy, str);
	char* command_text = strtok(str_copy, " \t\n");

	printf("got text\n");
	printf("%s\n", command_text);

	location* source = malloc(sizeof(location));
	location* target = malloc(sizeof(location));;

	source->row = -1;
	source->column = '-';
	target->row = -1;
	target->column = '-';

	Gamecommand game_command;
	game_command.validArg = false;

	// char* command_int = strtok(NULL, " \t\n");


	if (strcmp(command_text, "move") == 0){
		// need to be checked
		game_command.cmd = MOVE;

		printf("start\n");
		source->row = atoi(strtok(str_copy, "<,>"));
		printf("phase1\n");
		printf("first arg is: %d", source->row);
		source->column = strtok(str_copy, "<,>")[0];
		printf("phase2\n");
		printf("second arg is: %c", source->column);
		target->row = atoi(strtok(str_copy, "<,>"));
		printf("phase3\n");
		printf("third arg is: %d", target->row);
		target->column = strtok(str_copy, "<,>")[0];
		printf("phase4\n");
		printf("forth arg is: %c", target->column);

		//TODO -- need to verify that locations are intialized well
		game_command.move->source = source;
		game_command.move->dest = target;
		game_command.validArg = true;

		return game_command;
	}

	if (strcmp(command_text, "quit") == 0){
		game_command.cmd = GAME_QUIT;
		game_command.validArg = true;
		return game_command;
	}

	if (strcmp(command_text, "undo") == 0){
		game_command.cmd = UNDO;
		game_command.validArg = true;
		return game_command;
	}

	if (strcmp(command_text, "reset") == 0){
		game_command.cmd = RESET;
		game_command.validArg = true;
		return game_command;
	}

	if (strcmp(command_text, "reset") == 0){
		game_command.cmd = RESET;
		game_command.validArg = true;
		return game_command;
	}

	if (strcmp(command_text, "save") == 0){
		//need to complete saving mode
		game_command.cmd = SAVE;
		game_command.validArg = true;
		return game_command;
	}
	return game_command;
}




