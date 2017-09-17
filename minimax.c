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

	// in case of mate give more points

	if (has_valid_moves(game) == false){
		change_turn(game);
		if  (is_check(game) == true){
			if (current_turn_color(game) == 1){
				return 1000;
			}
			else{
				return -1000;
			}
		}
		change_turn(game);
	}

	for (int i = 0; i < 16; i++) {

		char cur_piece_type = game->whites[i]->piece_type;
		if (cur_piece_type == WHITE_PAWN && game->whites[i]->alive == 1) {
			white_sum += 1;
		}
		if ((cur_piece_type == WHITE_BISHOP || cur_piece_type == WHITE_KNIGHT) && game->whites[i]->alive == 1) {
			white_sum += 3;
		}
		if (cur_piece_type == WHITE_ROOK && game->whites[i]->alive == 1) {
			white_sum += 5;
		}
		if (cur_piece_type == WHITE_QUEEN && game->whites[i]->alive == 1) {
			white_sum += 9;
		}
		if (cur_piece_type == WHITE_KING && game->whites[i]->alive == 1) {
			white_sum += 100;
		}
	}

	//calculate black pieces
	for (int i = 0; i < 16; i++) {
		char cur_piece_type = game->blacks[i]->piece_type;
		if (cur_piece_type == BLACK_PAWN && game->blacks[i]->alive == 1) {
			black_sum += 1;
		}
		if ((cur_piece_type == BLACK_BISHOP || cur_piece_type == BLACK_KNIGHT) && game->blacks[i]->alive == 1 ) {
			black_sum += 3;
		}
		if (cur_piece_type == BLACK_ROOK && game->blacks[i]->alive == 1) {
			black_sum += 5;
		}
		if (cur_piece_type == BLACK_QUEEN && game->blacks[i]->alive == 1) {
			black_sum += 9;
		}
		if (cur_piece_type == BLACK_KING && game->blacks[i]->alive == 1) {
			black_sum += 100;
		}
	}
	// if it's the white player's turn:



	if (current_turn_color(game) == 1) {
		score = white_sum - black_sum;
	} else {
		score = black_sum - white_sum;
	}
	return -score;
}


// returns the move the computer should do, the move will be in best_move
int alphabeta(game* node, int depth, int alpha, int beta, bool maximizing_player, move* best_move){
	if (depth == 0){
		return scoring_function(node);
	}

	// variables definition
	int tmp_score;
	int new_score;
	piece** your_pieces;
	piece* tmp_piece;
	move* tmp_move = create_move();
	int color = (node->current_turn + node->user_color + 1)%2;
	location** valid_locs = malloc(64*sizeof(location*));
	move* tmp_best_move = create_move();
	bool quit = false;
	int total_possible_moves = 0;

	// allocating memory for moves
	for (int i=0; i<64; i++){
		valid_locs[i] = create_location();
	}

	// maximize
	if (maximizing_player == true){
		tmp_score = -10000000;
		if (color == 0){
			your_pieces = node->blacks;
		}
		else{
			your_pieces = node->whites;
		}

		// all_valid_moves(node, possible_moves, amount_of_valid_moves);
		for (int i=0; i<16; i++){
			if (quit == true){
				break;
			}
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
					total_possible_moves += 1;

					move_piece(tmp_game, tmp_move, location_to_piece(tmp_game, tmp_move->source));

					new_score = alphabeta(tmp_game, depth-1, alpha, beta, false, best_move);

					game_destroy(tmp_game);

					if (tmp_best_move->source->row == -1 || new_score < tmp_score){
						tmp_best_move->source->row = tmp_move->source->row;
						tmp_best_move->source->column = tmp_move->source->column;
						tmp_best_move->dest->row = tmp_move->dest->row;
						tmp_best_move->dest->column = tmp_move->dest->column;
						tmp_score = new_score;
					}

					if (new_score > alpha){
						tmp_best_move->source->row = tmp_move->source->row;
						tmp_best_move->source->column = tmp_move->source->column;
						tmp_best_move->dest->row = tmp_move->dest->row;
						tmp_best_move->dest->column = tmp_move->dest->column;
						alpha = new_score;
						tmp_score = new_score;
					}

					if (beta <= alpha){
						tmp_best_move->source->row = -1;
						tmp_score = beta;
						quit = true;
						break; // beta cut-off
					}
				}
			}
		}
	}

	else{
		tmp_score = 10000000;
		if (color == 0){
			your_pieces = node->blacks;
		}

		else{
			your_pieces = node->whites;
		}

		// all_valid_moves(node, possible_moves, amount_of_valid_moves);
		for (int i=0; i<16; i++){
			if (quit == true){
				break;
			}
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
					total_possible_moves += 1;

					move_piece(tmp_game, tmp_move, location_to_piece(tmp_game, tmp_move->source));

					new_score = alphabeta(tmp_game, depth-1, alpha, beta, true, best_move);

					game_destroy(tmp_game);

					if (tmp_best_move->source->row == -1  || new_score > tmp_score){
						tmp_best_move->source->row = tmp_move->source->row;
						tmp_best_move->source->column = tmp_move->source->column;
						tmp_best_move->dest->row = tmp_move->dest->row;
						tmp_best_move->dest->column = tmp_move->dest->column;
						tmp_score = new_score;
					}

					if (new_score < beta){
						tmp_best_move->source->row = tmp_move->source->row;
						tmp_best_move->source->column = tmp_move->source->column;
						tmp_best_move->dest->row = tmp_move->dest->row;
						tmp_best_move->dest->column = tmp_move->dest->column;
						beta = new_score;
						tmp_score = new_score;
					}

					if (beta <= alpha){
						tmp_best_move->source->row = -1;
						tmp_score = alpha;
						quit = true;
						break; // alpha cut-off
					}
				}
			}
		}
	}
	// freeing all variables
	for (int i=0; i<64; i++){
		destroy_location(valid_locs[i]);
	}

	free(valid_locs);
	destroy_move(tmp_move);

	// if no moves were checked don't update tmp_best_move!
	if (total_possible_moves != 0){
		best_move->dest->row = tmp_best_move->dest->row;
		best_move->dest->column = tmp_best_move->dest->column;

		best_move->source->row = tmp_best_move->source->row;
		best_move->source->column = tmp_best_move->source->column;
	}
	destroy_move(tmp_best_move);
	return tmp_score;
}

move* get_recommended_move_for_comp(game* game, int depth){
	move* comp_move = create_move();
	// user is black
	if (game->user_color == 0){
		alphabeta(game, depth, INT_MIN, INT_MAX, false, comp_move);
	}

	// user is white
	if (game->user_color == 1){
		alphabeta(game, depth, INT_MIN, INT_MAX, true, comp_move);
	}
	return comp_move;
}








