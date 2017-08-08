/*
 * game.c
 *
 *  Created on: Aug 6, 2017
 *      Author: Gal
 */

#include "game.h"

void print_board(game* cur_game){

	if (cur_game == NULL)
		return ;

	for (int i=8; i>0; i--){
		printf("  %d|"%i);
		for (int j=0; j<8 ; j++){
			printf("%c "%cur_game->board[i][j]);
		}
		printf("|\n");
	}
	printf(" -----------------\n   ");
	for (char c="A"; c<="H"; c++){
		printf("%c "%c);
	}
}

bool check_diagonals(game* cur_game, location king_loc, location enemy_loc){
	// up right diagonal
	for (int i=0; i<8; i++){

		if ((enemy_loc->row + i == king_loc->row) && (enemy_loc->column + i == king_loc->column)){
			return true;
		}

		if (enemy_loc->row + i > 8 || enemy_loc->column + i > 8){
			continue;
		}

		if (cur_game->board[enemy_loc->row + i][enemy_loc->column + i] != EMPTY_ENTRY){
			continue;
		}
	}

	// up left diagonal
	for (int i=0; i<8; i++){
		if (enemy_loc->row - i < 0 || enemy_loc->column+ i > 8){
			continue;
		}
		if (enemy_loc->row - i == king_loc->row && enemy_loc->column+ i == king_loc->y){
			return true;
		}
	}

	// down left diagonal
	for (int i=0; i<8; i++){
		if (enemy_loc->row - i < 0 || enemy_loc->column- i < 0){
			continue;
		}
		if (enemy_loc->row - i == king_loc->row && enemy_loc->column- i == king_loc->y){
			return true;
		}
	}

	// down right diagonal
	for (int i=0; i<8; i++){
		if (enemy_loc->row + i < 8 || enemy_loc->column- i > 0){
			continue;
		}
		if (enemy_loc->row + i == king_loc->row && enemy_loc->column- i == king_loc->y){
			return true;
		}
	}
}

bool check_parallels(game* cur_game, location king_loc, location enemy_loc){
	// up
	for (int i=0; i<8; i++){
		if (enemy_loc->column+ i > 8){
			continue;
		}
		if (enemy_loc->column+ i == king_loc->column && enemy_loc->row  == king_loc->x){
			return true;
		}
	}

	// down
	for (int i=0; i<8; i++){
		if (enemy_loc->column- i < 0){
			continue;
		}
		if (enemy_loc->column- i == king_loc->column&& enemy_loc->row  == king_loc->x){
			return true;
		}
	}

	// right
	for (int i=0; i<8; i++){
		if (enemy_loc->row + i > 8){
			continue;
		}
		if (enemy_loc->row + i == king_loc->row && enemy_loc->column == king_loc->y){
			return true;
		}
	}

	// left
	for (int i=0; i<8; i++){
		if (enemy_loc->row - i < 0){
			continue;
		}
		if (enemy_loc->row - i == king_loc->row && enemy_loc->column == king_loc->y){
			return true;
		}
	}
}

bool is_check(game* cur_game, const piece king, const piece* enemy_locs){

	if (cur_game == NULL){
		return false;
	}

	// finds the loaction of the white king
	location king_loc = king->piece_location;
	location enemy_loc;

	for (int i=0; i<16; i++){
		// putting location into variable for readability
		enemy_loc = *(enemy_locs + i)->piece_location;

		// black pawn
		if (*(enemy_locs + i)->piece_type == BLACK_PAWN){
			if ((enemy_loc->column = (king_loc->column) + 1) &&
					((enemy_loc->row = (king_loc->row) + 1) ||(enemy_loc->row = (king_loc->row) - 1))){
				return true;
			}
		}

		// white pawn
		if (*(enemy_locs + i)->piece_type == BLACK_PAWN){
			if ((enemy_loc->column = (king_loc->column) - 1) &&
					((enemy_loc->row = (king_loc->row) + 1) ||(enemy_loc->row = (king_loc->row) - 1))){
				return true;
			}
		}

		// knight
		if (*(enemy_locs + i)->piece_type == BLACK_KNIGHT || *(enemy_locs + i)->piece_type == WHITE_KNIGHT){
			if (((enemy_loc->column = (king_loc->column) + 2) && ((enemy_loc->row = (king_loc->row) + 1) ||(enemy_loc->row = (king_loc->row) - 1))) ||
				((enemy_loc->column = (king_loc->column) - 2) && ((enemy_loc->row = (king_loc->row) + 1) ||(enemy_loc->row = (king_loc->row) - 1)))||
				((enemy_loc->row = (king_loc->row) + 2) && ((enemy_loc->column = (king_loc->column) + 1) ||(enemy_loc->column = (king_loc->column) - 1)))||
				((enemy_loc->row = (king_loc->row) - 2) && ((enemy_loc->column = (king_loc->column) + 1) ||(enemy_loc->column = (king_loc->column) - 1)))){
				return true;
			}
		}

		// bishop
		if (*(enemy_locs + i)->piece_type == BLACK_BISHOP || *(enemy_locs + i)->piece_type == WHITE_BISHOP){
			if (check_diagonals(cur_game, king->piece_location, *(enemy_locs + i)->piece_location) == true){
				return true;
			}
		}

		// rook
		if (*(enemy_locs + i)->piece_type == BLACK_ROOK || *(enemy_locs + i)->piece_type == WHITE_ROOK){
			if (check_parallels(cur_game, king->piece_location, *(enemy_locs + i)->piece_location) == true){
				return true;
			}
		}

		// queen
		if (*(enemy_locs + i)->piece_type == BLACK_QUEEN || *(enemy_locs + i)->piece_type == WHITE_QUEEN){
			if ((check_parallels(cur_game, king->piece_location, *(enemy_locs + i)->piece_location) == true) ||
				(check_diagonals(cur_game, king->piece_location, *(enemy_locs + i)->piece_location) == true)){
				return true;
			}
		}

		// king
		if (*(enemy_locs + i)->piece_type == BLACK_KING || *(enemy_locs + i)->piece_type == WHITE_KING){
			if (((king.piece_location->row - (*(enemy_locs + i)->piece_location->row)) < 1 && (king.piece_location->row - (*(enemy_locs + i)->piece_location->row)) > -1) &&
				((king.piece_location->column - (*(enemy_locs + i)->piece_location->column)) < 1 && (king.piece_location->column - (*(enemy_locs + i)->piece_location->column)) > -1)){
				return true;
			}
		}

		return false;
	}
}
