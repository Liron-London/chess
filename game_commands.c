/*
 * game_command.c
 *
 *  Created on: Aug 19, 2017
 *      Author: Gal
 */
#include "game_commands.h"

Gamecommand* game_command_create(){
	Gamecommand* game_command = malloc(sizeof(Gamecommand));
	if (game_command == NULL) {
		free(game_command);
		return NULL;
	}
	game_command->validArg = false;
	game_command->cmd = ILLIGAL_COMMAND;
	game_command->move = create_move();
	if (game_command->move == NULL) {
		game_command_destroy(game_command);
		return NULL;
	}
	return game_command;
}

void game_command_destroy(Gamecommand* command) {
	destroy_move(command->move);
	free(command);
}

/* TODO -
 * there is a memory leak in this function - need to free locations in the end of use
 * in move, need to make sure that the input is legal
 * need to free game_command
 *
*/
Gamecommand* game_command_parse_line(char* str){
	char* str_copy = malloc(strlen(str) + 1);
	if (str_copy == NULL){
		free(str_copy);
		return NULL;
	}
	strcpy(str_copy, str);
	char* command_text = strtok(str_copy, " \t\n");

	Gamecommand* game_command = game_command_create();
	game_command->validArg = false;

	// char* command_int = strtok(NULL, " \t\n");

	if (strcmp(command_text, "move") == 0){
		//printf("DEBUG: detected that command is move\n");
		game_command->cmd = MOVE;

		game_command->move->source->row = atoi(strtok(NULL, "<, ")) - 1;
		game_command->move->source->column = strtok(NULL, "<,> ")[0] - 'A';

		// command_text is printed because the variable must be in use
		char* command_text = strtok(NULL, " \t\n");
		//printf("DEBUG: command_text is: %s\n", command_text);
		if (strcmp(command_text, "to") != 0){
			// game_command->is_val is false...
			return game_command;
		}
		game_command->move->dest->row = atoi(strtok(NULL, "<, ")) - 1;
		game_command->move->dest->column = strtok(NULL, "<,> ")[0] - 'A';

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
	// char command_str[1024]; // assuming that the command is no longer the 1024 chars
	piece* cur_piece;

	while (1){
		char* command_str = (char*) malloc(1024*sizeof(char));
		printf("please choose a command\n"); // need to be changed
		scanf(" %1024[^\n]", command_str);
		printf("DEBUG: scanf passed\n");
		printf("DEBUG: text is %s\n", command_str);
		game_command = game_command_parse_line(command_str);
		printf("DEBUG: prase the line!\n");

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
			printf("DEBUG: Current turn is: %d\n", game->current_turn);
			if (is_valid_move(game, game_command->move) == true){
				printf("DEBUG: is_valid_move is OK\n");
				cur_piece = location_to_piece(game, game_command->move->source);
				printf("DEBUG: location_to_piece is OK\n");
				printf("DEBUG: current piece is %c %d %d\n", cur_piece->piece_type, cur_piece->piece_location->row,cur_piece->piece_location->column);
				move_piece(game, game_command->move, cur_piece);
				printf("DEBUG: move_piece is OK\n");
				print_board(game);
				printf("valid move!\n");
			}

			else{
				printf("DEBUG: move is not valid!\n");
			}

			// update history
			// return 1;
		}
		free(command_str);
		game_command_destroy(game_command);
	}
}


