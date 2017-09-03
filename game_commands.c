/*
 * game_command.c
 *
 *  Created on: Aug 19, 2017
 *      Author: Gal
 */
#include "game_commands.h"
#include "file_handler.h"
#include "debug.h"
#include "array_list.h"

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

	// relevant only in one player mode -- need to create history array
	array_list* history = array_list_create(6);

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
			// freeing all variables
			array_list_destroy(history);
			free(command_str);
			game_command_destroy(game_command);
			game_destroy(game);
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

				// update history
				if (game->game_mode == 1){
					if (array_list_is_full(history) == true){
						array_list_remove_first(history);
					}
					array_list_add_last(history, game_copy(game), copy_move(game_command->move));
				}

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
		}

		// UNDO
		if (game_command->validArg == true && game_command->cmd == UNDO){
			DEBUG("In UNDO\n");
			if (game->game_mode != 1){
				printf("Undo command not avaialbe in 2 players mode\n");
			}

			else{
				if (array_list_is_empty(history) == true){
					printf("Empty history, move cannot be undone\n");
				}

				else{
					DEBUG("history is not empty!\n");
					// takes 2 moves and games out of history
					move* tmp_move = create_move();
					DEBUG("move created!\n");
					tmp_move = array_list_get_last_move(history);

					if (game->user_color == 0){
						printf("Undo move for player white : <%d, %d> -> <%d, %d>\n", tmp_move->dest->row, tmp_move->dest->column, tmp_move->source->row, tmp_move->source->column);
						array_list_remove_last(history);
						tmp_move = array_list_get_last_move(history);
						printf("Undo move for player black : <%d, %d> -> <%d, %d>\n", tmp_move->dest->row, tmp_move->dest->column, tmp_move->source->row, tmp_move->source->column);
					}

					else{
						printf("Undo move for player black : <%d, %d> -> <%d, %d>\n", tmp_move->dest->row, tmp_move->dest->column, tmp_move->source->row, tmp_move->source->column);
						array_list_remove_last(history);
						tmp_move = array_list_get_last_move(history);
						printf("Undo move for player white : <%d, %d> -> <%d, %d>\n", tmp_move->dest->row, tmp_move->dest->column, tmp_move->source->row, tmp_move->source->column);
					}

					//updating game and history
					game = array_list_get_last_game(history);
					array_list_remove_last(history);
					destroy_move(tmp_move);
					print_board(game);
				}
			}
		}

		free(command_str);
		game_command_destroy(game_command);
	}
return 0;
}


