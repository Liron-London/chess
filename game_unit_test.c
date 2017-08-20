/*
 * game_unit_test.c
 *
 *  Created on: Aug 12, 2017
 *      Author: lironl
 */
# include "game.h"

static bool verify_game_obj(game* test_game) {
	//test default fields
	if (test_game->game_mode != 1 ||
			test_game->difficulty != 2 ||
			test_game->user_color != 1 ||
			test_game->current_turn != 1) {
		printf("Error initializing new game\n");
		return false;
	}

	/*test history
	for (int i = 0; i < 6; i++) {
		if (test_game->history->elements[i] != 0) {
			printf("Error initializing game history\n");
			return false;
		}
	}*/

	return true;

}

static bool game_create_test() {
	game* test_game = game_create();
	printf("created game instance\n");
	return verify_game_obj(test_game);
}

static bool game_copy_test() {
	game* first_game = game_create();
	game* copy = game_copy(first_game);
	bool success = verify_game_obj(copy);
	return success;
}

static bool game_destroy_test() {
	game* test_game = game_create();
	//printf("before destroy\n");
	game_destroy(test_game);
	//printf("after destroy\n");
	return true;
}

static bool game_print_test() {
	game* test_game = game_create();
	print_board(test_game);
	return true;
}

static bool move_pawns_check(){
	game* game = game_create();
	print_board(game);
	Gamecommand game_command;
	game_command = game_command_parse_line("move <2,B> to <2,C>");
	move_piece(game, game_command.move, &(game->whites[8]));
	print_board(game);
	return true;
}

int main() {
	bool success = game_create_test();
	if(success) {
		printf("Game create success\n");
	}
	success = game_copy_test();
	if(success) {
		printf("Game copy success\n");
	}
	success = game_destroy_test();
	if(success) {
		printf("Game destroy success\n");
	}
	success = game_print_test();
	if(success) {
		printf("Game print success\n");
	}

	success = move_pawns_check();
	if(success) {
		printf("Game print success\n");
	}


	if(!success) {
		printf("Undetected error\n");
		return 1;
	}

	return 0;
}

