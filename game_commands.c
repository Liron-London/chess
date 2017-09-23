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
		//check for invalid move parameters
//		if (game_command->move->source == NULL ||
//				game_command->move->source->row < 0 || game_command->move->source->row > 7 ||
//				game_command->move->source->column < 0 || game_command->move->source->column > 7) {
//			announce_invalid_location();
//			game_command->validArg = false;
//		}

		// command_text is printed because the variable must be in use
		char* command_text = strtok(NULL, " \t\n");
		//DEBUG("command_text is: %s\n", command_text);
		if (strcmp(command_text, "to") != 0){
			// game_command->is_val is false...
			free(str_copy);
			return game_command;
		}
		game_command->move->dest->row = atoi(strtok(NULL, "<, ")) - 1;
		game_command->move->dest->column = strtok(NULL, "<,> ")[0] - 'A';

		game_command->validArg = true;
		free(str_copy);
		return game_command;
	}

	if (strcmp(command_text, "quit") == 0){
		game_command->cmd = GAME_QUIT;
		game_command->validArg = true;
		free(str_copy);
		return game_command;
	}

	if (strcmp(command_text, "undo") == 0){
		game_command->cmd = UNDO;
		game_command->validArg = true;
		free(str_copy);
		return game_command;
	}

	if (strcmp(command_text, "reset") == 0){
		game_command->cmd = RESET;
		game_command->validArg = true;
		free(str_copy);
		return game_command;
	}

	if (strcmp(command_text, "save") == 0) {
		strcpy(file_name, strtok(NULL, " \t\n"));
		//DEBUG("in parse line, file_name is: %s\n", file_name);
		game_command->cmd = SAVE;
		game_command->validArg = true;
		free(str_copy);
		return game_command;
	}

	free(str_copy);
	return game_command;
}

void ask_for_move(game* cur_game) {
	//player 1's turn, player 1 is white OR player 2's turn, player 1 is black
	if ((cur_game->current_turn == 1 && cur_game->user_color == 1) ||
			(cur_game->current_turn == 0 && cur_game->user_color == 0)) {
		printf("white player - enter your move:\n");
	} else {
		printf("black player - enter your move:\n");
	}
}

void announce_invalid_location() {
	printf("Invalid position on the board\n");
}

void announce_empty_history() {
	printf("Empty history, move cannot be undone\n");
}

void announce_undo_not_available() {
	printf("Undo command not available in 2 players mode\n");
}

void announce_undo_move(int player, move* tmp_move) {
	int src_row, dst_row;
	char src_col, dst_col;
	char* player_color;
	if (player == 1) {
		player_color = "white";
	} else {
		player_color = "black";
	}
	dst_row = tmp_move->dest->row+1;
	dst_col = tmp_move->dest->column+'A';
	src_row = tmp_move->source->row+1;
	src_col = tmp_move->source->column+'A';
	printf("Undo move for player %s : <%d, %c> -> <%d, %c>\n",
			player_color, dst_row, dst_col, src_row, src_col);

}


void announce_computer_move(game* game, move* move){
	char piece_type = location_to_piece(game, move->source)->piece_type;
	if (piece_type == 'm' || piece_type == 'M'){
		printf("Computer: move pawn at <%d,%c> to <%d,%c>\n", move->source->row,
				move->source->column + 'A', move->dest->row, move->dest->column + 'A');
	}
	if (piece_type == 'n' || piece_type == 'N'){
		printf("Computer: move knight at <%d,%c> to <%d,%c>\n", move->source->row,
				move->source->column + 'A', move->dest->row, move->dest->column + 'A');
	}
	if (piece_type == 'b' || piece_type == 'B'){
		printf("Computer: move bishop at <%d,%c> to <%d,%c>\n", move->source->row,
				move->source->column + 'A', move->dest->row, move->dest->column + 'A');
	}
	if (piece_type == 'q' || piece_type == 'Q'){
		printf("Computer: move queen at <%d,%c> to <%d,%c>\n", move->source->row,
				move->source->column + 'A', move->dest->row, move->dest->column + 'A');
	}
	if (piece_type == 'k' || piece_type == 'K'){
		printf("Computer: move king at <%d,%c> to <%d,%c>\n", move->source->row,
				move->source->column + 'A', move->dest->row, move->dest->column + 'A');
	}
	if (piece_type == 'r' || piece_type == 'R'){
		printf("Computer: move rook at <%d,%c> to <%d,%c>\n", move->source->row,
				move->source->column + 'A', move->dest->row, move->dest->column + 'A');
	}
}

void announce_quit() {
	printf("Exiting...\n");
}

void announce_reset() {
	printf("Restarting...\n");
}


void announce_mate(int color) {
	color = (color + 1) % 2;
	char* color_name;
	if (color == 1) {
		color_name = "white";
	} else {
		color_name ="black";
	}
	printf("Checkmate! %s player wins the game\n", color_name);
}

void announce_tie() {
	printf("The game ends in a tie\n");
}

// called when the command "start" is pressed in settings
int game_play(game* game){
	Gamecommand* game_command;
	// char command_str[1024]; // assuming that the command is no longer the 1024 chars
	piece* cur_piece;
	if(!(game->game_mode == 1 && game->user_color == 0)) {
		print_board(game);
	}
	// relevant only in one player mode -- need to create history array
	array_list* history = array_list_create(6);
	while (1){

		// computer's turn
		if (game->game_mode == 1 && game->current_turn == 0){
			move* comp_move;
			comp_move = get_recommended_move_for_comp(game, game->difficulty);
			announce_computer_move(game, comp_move);
			move_piece(game, comp_move, location_to_piece(game, comp_move->source));
			print_board(game);
			// update history
			if (array_list_is_full(history) == true){
				array_list_remove_first(history);
			}
			array_list_add_last(history, game_copy(game), copy_move(comp_move));
			destroy_move(comp_move);
			int color = current_turn_color(game);
			if (has_valid_moves(game) == false){
				if (is_check(game) == true){
					announce_mate(color);
				}
				else{
					announce_tie();
				}
				break;

			}
			if (is_check(game)) {
				announce_check((current_turn_color(game) + 1)%2);
			}

		}

		char* command_str = (char*) malloc(1024*sizeof(char));
		char file_name[256] = "default_game.xml";
		ask_for_move(game);
		scanf(" %1024[^\n]", command_str);

		game_command = game_command_parse_line(command_str, file_name);

		// QUIT
		if (game_command->validArg == true && game_command->cmd == GAME_QUIT) {
			// freeing all variables
			array_list_destroy(history);
			free(command_str);
			game_command_destroy(game_command);
			game_destroy(game);
			announce_quit();
			exit(1);
			//return 1;
		}

		//RESET
		if (game_command->validArg == true && game_command->cmd == RESET) {
			// freeing all variables
			array_list_destroy(history);
			free(command_str);
			game_command_destroy(game_command);
			game_destroy(game);
			announce_reset();
			set_game();
			return 0;
		}

		//SAVE
		if (game_command->validArg == true && game_command->cmd == SAVE){
			save_game(game, file_name);
		}

		// MOVE
		if (game_command->validArg == true && game_command->cmd == MOVE){
			// check if valid move
			if (is_valid_move(game, game_command->move) == true){

				// update history
				if (game->game_mode == 1){
					if (array_list_is_full(history) == true){
						array_list_remove_first(history);
					}
					array_list_add_last(history, game_copy(game), copy_move(game_command->move));
				}

				cur_piece = location_to_piece(game, game_command->move->source);
				move_piece(game, game_command->move, cur_piece);

				int color = current_turn_color(game);
				if (has_valid_moves(game) == false){
					change_turn(game);
					if (is_check(game) == true){
						color = current_turn_color(game);
						announce_mate(color);
						change_turn(game);
					}
					else{
						announce_tie();
					}
					free(command_str);
					game_command_destroy(game_command);
					break;
				}
				change_turn(game);
				if (is_check(game) == true){
					color = current_turn_color(game);
					announce_check(color);
				}
				change_turn(game);
				print_board(game);
			}
		}

		// UNDO
		if (game_command->validArg == true && game_command->cmd == UNDO){
			DEBUG("In UNDO\n");
			if (game->game_mode != 1){
				announce_undo_not_available();
			}

			else {
				if (array_list_is_empty(history) == true){
					announce_empty_history();
				}

				else {
					DEBUG("history is not empty!\n");
					// takes 2 moves and games out of history
					move* tmp_move = create_move();
					DEBUG("move created!\n");
					tmp_move = array_list_get_last_move(history);
					announce_undo_move(current_turn_color(game), tmp_move);
					array_list_remove_last(history);
					tmp_move = array_list_get_last_move(history);
					announce_undo_move((current_turn_color(game)+1)%2, tmp_move);

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

	array_list_destroy(history);
	game_destroy(game);
return 0;
}
