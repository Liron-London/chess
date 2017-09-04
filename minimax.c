/*
 * minimax.c
 *
 *  Created on: Aug 12, 2017
 *      Author: lironl
 */
#include "minimax.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define min(a,b)  ((((a)-(b))&0x80000000) >> 31)? (a) : (b)
#define max(a,b)  ((((a)-(b))&0x80000000) >> 31)? (b) : (a)

int scoring_function(game* game) {
	if (game == NULL) {
		return 0;
	}
	int score = 0;
	int white_sum = 0;
	int black_sum = 0;
	//calculate white pieces
	for (int i = 0; i < 16; i++) {
		char cur_piece_type = game->whites[i]->piece_type;
		if (cur_piece_type == WHITE_PAWN) {
			white_sum += 1;
		}
		if (cur_piece_type == WHITE_BISHOP || cur_piece_type == WHITE_KNIGHT) {
			white_sum += 3;
		}
		if (cur_piece_type == WHITE_ROOK) {
			white_sum += 5;
		}
		if (cur_piece_type == WHITE_QUEEN) {
			white_sum += 9;
		}
		if (cur_piece_type == WHITE_KING) {
			white_sum += 100;
		}
	}

	//calculate black pieces
	for (int j = 0; j < 16; j++) {
		char cur_piece_type = game->blacks[j]->piece_type;
		if (cur_piece_type == BLACK_PAWN) {
			black_sum += 1;
		}
		if (cur_piece_type == BLACK_BISHOP || cur_piece_type == BLACK_KNIGHT) {
			black_sum += 3;
		}
		if (cur_piece_type == BLACK_ROOK) {
			black_sum += 5;
		}
		if (cur_piece_type == BLACK_QUEEN) {
			black_sum += 9;
		}
		if (cur_piece_type == BLACK_KING) {
			black_sum += 100;
		}
	}
	// if it's the white player's turn:
	if ((game->current_turn == 1 && game->user_color == 1) ||
			(game->current_turn == 0 && game->user_color == 0)) {
		score = white_sum - black_sum;
	} else {
		score = black_sum - white_sum;
	}
	return score;
}

// put all valid moves in all_valid_moves, amount of valid moves is the size of the list
/*
void all_valid_moves(game* game, move** all_valid_moves, int* amout_of_valid_moves){
	int color = (game->current_turn + game->user_color)%2;
	piece** your_pieces;
	// white turn
	if (color == 0){
		your_pieces = game->whites;
	}
	else{
		your_pieces = game->blacks;
	}
	for (int i=0; i<16; i++){
		// piece is alive
		if (your_pieces->alive == 1){
			valid_moves()
		}
	}
	return NULL;
}*/

// returns the move the computer should do, the move will be in best_move
int alphabeta(game* node, int depth, int alpha, int beta, bool maximizing_player, move* best_move){
	if (depth == 0){
		//DEBUG2("Score is %d\n", scoring_function(node));
		return scoring_function(node);
	}

	DEBUG2("In alphabeta\n");
	DEBUG2("depth is %d\n", depth);

	int tmp_score;
	piece** your_pieces;
	piece* tmp_piece;
	move* tmp_move = create_move();
	int color = (node->current_turn + node->user_color)%2;
	location** valid_locs = malloc(64*sizeof(location*));
	// game* tmp_game = game_create();


	for (int i=0; i<64; i++){
		valid_locs[i] = create_location();
	}

	// only the minimum part
	if (maximizing_player == true){
		DEBUG2("******************\n");
		tmp_score = INT_MIN;
		if (color == 0){
			your_pieces = node->blacks;
		}

		else{
			your_pieces = node->whites;
		}


		// all_valid_moves(node, possible_moves, amount_of_valid_moves);
		for (int i=0; i<16; i++){
			if (your_pieces[i]->alive){
				tmp_piece = your_pieces[i];

				//TODO -- need to export to another func
				for (int k=0; k<64; k++){
					valid_locs[k]->row=-1;
					valid_locs[k]->column=-1;
				}

				valid_moves(valid_locs, node, tmp_piece);
				int j = 0;
				while (valid_locs[j]->row != -1){
					game* tmp_game = game_copy(node);

					tmp_move->source->row = tmp_piece->piece_location->row;
					tmp_move->source->column = tmp_piece->piece_location->column;
					tmp_move->dest->column = valid_locs[j]->column;
					tmp_move->dest->row = valid_locs[j]->row;

					j += 1;
					DEBUG2("J is %d\n", j);
					move_piece(tmp_game, tmp_move, location_to_piece(tmp_game, tmp_move->source));

					tmp_score = max(tmp_score, alphabeta(tmp_game, depth-1, alpha, beta, false, best_move));

					best_move = copy_move(tmp_move);
					alpha = max(alpha, tmp_score);
					game_destroy(tmp_game);

					if (beta <= alpha){
						break; // beta cut-off
					}
				}
			}
		}
	}

	else{
		DEBUG2("####################\n");
		tmp_score = INT_MAX;
		if (color == 0){
			your_pieces = node->blacks;
		}

		else{
			your_pieces = node->whites;
		}

		// all_valid_moves(node, possible_moves, amount_of_valid_moves);
		for (int i=0; i<16; i++){
			if (your_pieces[i]->alive){
				tmp_piece = your_pieces[i];

				//TODO -- need to export to another func
				for (int k=0; k<64; k++){
					valid_locs[k]->row=-1;
					valid_locs[k]->column=-1;
				}

				valid_moves(valid_locs, node, tmp_piece);
				int j = 0;
				while (valid_locs[j]->row != -1){
					game* tmp_game = game_copy(node);

					tmp_move->source->row = tmp_piece->piece_location->row;
					tmp_move->source->column = tmp_piece->piece_location->column;
					tmp_move->dest->column = valid_locs[j]->column;
					tmp_move->dest->row = valid_locs[j]->row;

					j += 1;
					DEBUG2("J is %d\n", j);
					move_piece(tmp_game, tmp_move, location_to_piece(tmp_game, tmp_move->source));

					tmp_score = min(tmp_score, alphabeta(tmp_game, depth-1, alpha, beta, false, best_move));

					best_move = copy_move(tmp_move);
					beta = min(beta, tmp_score);
					game_destroy(tmp_game);

					if (beta <= alpha){
						break; // beta cut-off
					}
				}
			}
		}
	}
	for (int i=0; i<64; i++){
		destroy_location(valid_locs[i]);
	}
	free(valid_locs);
	destroy_move(tmp_move);
	return tmp_score;
}

move* get_recommended_move_for_comp(game* game, int depth){
	move* comp_move = create_move();
	alphabeta(game, depth, INT_MIN, INT_MAX, true, comp_move);
	return comp_move;
}
