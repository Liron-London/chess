/*
 * minimax.c
 *
 *  Created on: Aug 12, 2017
 *      Author: lironl
 */
#include "minimax.h"
#include "moves.h"
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
void all_valid_moves(game* game, move** all_valid_moves, int* amout_of_valid_moves){
	return NULL;
}

// returns the move the computer should do, the move will be in best_move
int alphabeta(game* node, int depth, int alpha, int beta, bool maximizing_player, move** best_move){
	if (depth == 0){
		return scoring_function(node);
	}

	int amount_of_valid_moves = 0;
	move** possible_moves = calloc(500, sizeof(move*));
	int tmp_score;
	piece* tmp_piece;

	// only the minimum part
	if (maximizing_player == true){
		int tmp_score = INT_MIN;
		game* tmp_game = game_copy(node);

		all_valid_moves(node, possible_moves, &amount_of_valid_moves);
		for (int i=0; i<amount_of_valid_moves; i++){
			tmp_piece = location_to_piece(node, possible_moves[i]->source);
			tmp_game = move_piece(node, possible_moves[i], tmp_piece);
			best_move = &(possible_moves[i]);

			tmp_score = max(tmp_score, alphabeta(tmp_game, depth-1, alpha, beta, false, best_move));
			alpha = max(alpha, tmp_score);
			if (beta <= alpha){
				game_destroy(tmp_game);
				free(possible_moves);
				best_move = possible_moves[i];
				break; // beta cut-off
			}
		}
		return tmp_score;
	}
}

