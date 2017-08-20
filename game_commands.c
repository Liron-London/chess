/*
 * game_command.c
 *
 *  Created on: Aug 19, 2017
 *      Author: Gal
 */
#include "game_commands.h"

/* TODO -
 * there is a memory leak in this function - need to free locations in the end of use
 * in move, need to make sure that the input is legal
 *
*/
Gamecommand* game_command_parse_line(const char* str){
	char* str_copy = malloc(strlen(str) + 1);
	strcpy(str_copy, str);
	char* command_text = strtok(str_copy, " \t\n");

	printf("%s\n", command_text);

	location* source = malloc(sizeof(location));
	location* target = malloc(sizeof(location));;

	Gamecommand* game_command;
	game_command->validArg = false;

	// char* command_int = strtok(NULL, " \t\n");


	if (strcmp(command_text, "move") == 0){
		// need to be checked
		game_command->cmd = MOVE;

		source->row = atoi(strtok(NULL, "<,"));
		source->column = strtok(NULL, "<,>")[0];

		// command_text is printed because the variable must be in use
		char* command_text = strtok(NULL, " \t\n");
		printf("%s\n", command_text);

		target->row = atoi(strtok(NULL, "<,>"));
		target->column = strtok(NULL, "<,>")[0];

		game_command->move->source = source;
		game_command->move->dest = target;
		game_command->validArg = true;

		return game_command;
	}

	if (strcmp(command_text, "quit") == 0){
		game_command->cmd = GAME_QUIT;
		game_command->validArg = true;
		return game_command;
	}

	if (strcmp(command_text, "undo") == 0){
		game_command->cmd = UNDO;
		game_command->validArg = true;
		return game_command;
	}

	if (strcmp(command_text, "reset") == 0){
		game_command->cmd = RESET;
		game_command->validArg = true;
		return game_command;
	}

	if (strcmp(command_text, "reset") == 0){
		game_command->cmd = RESET;
		game_command->validArg = true;
		return game_command;
	}

	if (strcmp(command_text, "save") == 0){
		//need to complete saving mode
		game_command->cmd = SAVE;
		game_command->validArg = true;
		return game_command;
	}
	return game_command;
}

// called when the command "start" is pressed in settings
int game_play(game* game){
	Gamecommand* game_command;
	char command_str[1024]; // assuming that the command is no longer the 1024 chars
	// piece* cur_piece;

	while (1){
		printf("please choose a command"); // need to be changed
		scanf("%s", command_str);
		game_command = game_command_parse_line(command_str);

		// QUIT
		if (game_command->validArg == true && game_command->cmd == GAME_QUIT){
			return 1;
		}

		//SAVE
		if (game_command->validArg == true && game_command->cmd == SAVE){
			// TODO - complete this function
			return 1;
		}

		// MOVE
		if (game_command->validArg == true && game_command->cmd == MOVE){
			// check if valid move
			if (is_valid_move(game, game_command->move) == true){
				// move_piece(game, game_command->move, piece);
				printf("valid move");
			}

			// update history
			return 1;
		}

	}
}


