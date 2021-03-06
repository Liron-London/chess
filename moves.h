/*
 * moves.h
 *
 *  Created on: Aug 23, 2017
 *      Author: lironl
 */

#ifndef MOVES_H_
#define MOVES_H_
#include "game.h"

/*
 * assuming that a move is legal - update the board, change the turn.
 */
void move_piece(game* cur_game, move* cur_move, piece* cur_piece);

move* copy_move(move* cur_move);
/*
* returns a list of all valid moves, needs to call is_check to verify the King's not threatened
*/
void valid_moves(location** valid_locs, game* cur_game, piece* cur_piece);

move* create_move();

void destroy_move(move* move);

piece* copy_piece(piece* cur_piece);
/*
 * creates a copy of the game, performs the move, calls is_check, updates
 * location array
 */
bool is_check_aux(location** valid_locs, game* cur_game, piece* cur_piece, int next_row, int next_col, int i);

/*
 *  given a move and a board says if the move is legal or not
 */
bool is_valid_move(game* cur_game, move* cur_move);

bool has_valid_moves(game* cur_game);

#endif /* MOVES_H_ */
