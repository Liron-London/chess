/*
 * minimax.c
 *
 *  Created on: Aug 12, 2017
 *      Author: lironl
 */
# include "minimax.h"

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
	for (int i = 0; i < 16; i++) {
		char cur_piece_type = game->blacks[i]->piece_type;
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

