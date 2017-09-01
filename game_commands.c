/*
 * game_command.c
 *
 *  Created on: Aug 19, 2017
 *      Author: Gal
 */
#include "game_commands.h"
#include "file_handler.h"
#include "debug.h"

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
Gamecommand* game_command_parse_line(char* str, char* file_name) {
	char* str_copy = malloc(strlen(str) + 1);
	if (str_copy == NULL){
		free(str_copy);
		return NULL;
	}
	strcpy(str_copy, str);
	char* command_text = strtok(str_copy, " \t\n");

	Gamecommand* game_command = game_command_create();
	game_command->validArg = false;
	//this block prevents the "unused variable" warning for file_name
	while (file_name) {
		break;
	}
	if (strcmp(command_text, "move") == 0){
		//DEBUG("detected that command is move\n");
		game_command->cmd = MOVE;

		game_command->move->source->row = atoi(strtok(NULL, "<, ")) - 1;
		game_command->move->source->column = strtok(NULL, "<,> ")[0] - 'A';

		// command_text is printed because the variable must be in use
		char* command_text = strtok(NULL, " \t\n");
		//DEBUG("command_text is: %s\n", command_text);
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

	if (strcmp(command_text, "save") == 0) {
		strcpy(file_name, strtok(NULL, " \t\n"));
		//DEBUG("in parse line, file_name is: %s\n", file_name);
		game_command->cmd = SAVE;
		game_command->validArg = true;
		return game_command;
	}
	return game_command;
}

void ask_for_move(game* cur_game) {
	//player 1's turn, player 1 is white OR player 2's turn, player 1 is black
	if ((cur_game->current_turn == 1 && cur_game->user_color == 1) ||
			(cur_game->current_turn == 0 && cur_game->user_color == 0)) {
		printf("White player - enter your move:\n");
	} else {
		printf("Black player - enter your move:\n");
	}
}

// called when the command "start" is pressed in settings
int game_play(game* game){
	Gamecommand* game_command;
	// char command_str[1024]; // assuming that the command is no longer the 1024 chars
	piece* cur_piece;

	while (1){
		char* command_str = (char*) malloc(1024*sizeof(char));
		char file_name[256] = "default_game.xml";
		ask_for_move(game);
		scanf(" %1024[^\n]", command_str);
		DEBUG("scanf passed\n");
		DEBUG("text is %s\n", command_str);
		game_command = game_command_parse_line(command_str, file_name);
		DEBUG("in game_play, file_name is: %s\n", file_name);
		DEBUG("prase the line!\n");

		// QUIT
		if (game_command->validArg == true && game_command->cmd == GAME_QUIT){
			return 1;
		}

		//SAVE
		if (game_command->validArg == true && game_command->cmd == SAVE){
			save_game(game, file_name);
		}

		// MOVE
		if (game_command->validArg == true && game_command->cmd == MOVE){
			// check if valid move
			DEBUG("Current turn is: %d\n", game->current_turn);
			if (is_valid_move(game, game_command->move) == true){
				DEBUG("is_valid_move is OK\n");
				cur_piece = location_to_piece(game, game_command->move->source);
				DEBUG("location_to_piece is OK\n");
				DEBUG("current piece is %c %d %d\n", cur_piece->piece_type, cur_piece->piece_location->row,cur_piece->piece_location->column);
				move_piece(game, game_command->move, cur_piece);
				DEBUG("move_piece is OK\n");
				print_board(game);
				DEBUG("valid move!\n");
				if (is_mate(game) == true){
					printf("player %d wins!", (game->current_turn + game->user_color)%2);
				}
			}

			else{
				DEBUG("move is not valid!\n");
			}
			// update history
			// return 1;
		}
		free(command_str);
		game_command_destroy(game_command);
	}
return 0;
}


