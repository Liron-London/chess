/*
 * game_command_unitest.c
 *
 *  Created on: Aug 19, 2017
 *      Author: Gal
 */

#include "moves.h"
#include "game_commands.h"
#include <stdbool.h>
#include "minimax.h"


/*
static bool basic_check(){
	// game* game = game_create();
	// return true;
	Gamecommand* game_command;

	game_command = game_command_parse_line("move <2,A> to <3,B>");
	printf("%d\n", game_command->move->source->row);
	printf("%d\n", game_command->move->source->column);
	printf("%d\n", game_command->move->dest->row);
	printf("%d\n", game_command->move->dest->column);
	game_command_destroy(game_command);
	return true;
}
*/

static bool game_play_check(){
	game* cur_game = game_create();
	print_board(cur_game);
	game_play(cur_game);
	return true;
}

static bool comp_move_check(){
	game* cur_game = game_create();
	print_board(cur_game);
	move* cur_move = create_move();
	cur_move = get_recommended_move_for_comp(cur_game, 4);
	piece* my_piece = location_to_piece(cur_game, cur_move->source);
	move_piece(cur_game, cur_move, my_piece);
	print_board(cur_game);
	destroy_move(cur_move);
	return true;
}


int main() {
	bool success;
//	success = basic_check();
//	printf("before last if\n");
//	if (success)
//		printf("basic game_commands checks success!\n");
	success = comp_move_check();
		if (success)
			printf("game_play test success!\n");
	return 0;

	success = game_play_check();
		if (success)
			printf("game_play test success!\n");
	return 0;
}
