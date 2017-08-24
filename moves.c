/*
 * moves.c
 *
 *  Created on: Aug 23, 2017
 *      Author: lironl
 */
#include "moves.h"

int color_by_type(char piece_type) {
	if ('A' <= piece_type && piece_type <= 'Z') {
		return 0;
	}
	return 1;
}

bool check_capturing(char piece_in_next_loc, int color) {
	if (piece_in_next_loc != EMPTY_ENTRY &&
			color_by_type(piece_in_next_loc) != color) {
		return true;
	}
	return false;
}


move* create_move(){
	move* move = malloc(sizeof(move));
	if (move == NULL){
		free(move);
		return NULL;
	}
	move->source = malloc(sizeof(location));
	if (move->source == NULL){
		free(move->source);
		free(move);
		return NULL;
	}
	move->dest = malloc(sizeof(location));
	if (move->source == NULL){
		free(move->dest);
		free(move->source);
		free(move);
		return NULL;
	}
	return move;
}

void destroy_move(move* move){
	free(move->dest);
	free(move->source);
	free(move);
}


bool is_check_aux(location* valid_locs, game* cur_game, piece* cur_piece,
		int next_row, int next_col, int i) {
	bool valid_move = false;
	game* tmp_game = game_copy(cur_game);
	move* tmp_move = create_move();
	tmp_move->source = cur_piece->piece_location; // source_location is always the piece location

	tmp_move->dest->row = next_row;
	tmp_move->dest->column = next_col;
	move_piece(tmp_game, tmp_move, cur_piece);
	if (is_check(tmp_game) == false) {
		valid_locs[i].row = next_row;
		valid_locs[i].column = next_col;
		valid_move = true;
	}
	free(tmp_move);
	free(tmp_game);
	return valid_move;
}

location* pawn_valid_moves(location* valid_locs, game* cur_game, piece* cur_piece) {
	printf("In pawn valid moves\n"); // debug
	int i = 0;
	char type = cur_piece->piece_type;
	int row = cur_piece->piece_location->row;
	int col = cur_piece->piece_location->column;

	printf("DEBUG: ROW IS %d\n COL IS %d\n", row, col);

	if (type == WHITE_PAWN) {
		if (row == 1 && cur_game->board[2][col] == EMPTY_ENTRY &&
				cur_game->board[3][col] == EMPTY_ENTRY) {

			printf("passed the basic checks...\n"); // debug

			// make the move on a copy of the board and check if is_check == true
			if(is_check_aux(valid_locs, cur_game, cur_piece, 3, col, i)) {
				i++;
			}
		}
		if (row < 7 && cur_game->board[row + 1][col] == EMPTY_ENTRY) {
			if (is_check_aux(valid_locs, cur_game, cur_piece, row + 1, col, i)) {
				i++;
			}
		}
		// if board[i][j] is black
		if (row < 7 && col < 7 &&
				color_by_type(cur_game->board[row + 1][col + 1]) == 0) {

			if (is_check_aux(valid_locs, cur_game, cur_piece, row + 1, col + 1, i)) {
				i++;
			}
		}

		if (row < 7 && col > 0 &&
				color_by_type(cur_game->board[row + 1][col + 1]) == 0) {
			if (is_check_aux(valid_locs, cur_game, cur_piece, row + 1, col - 1, i)) {
				i++;
			}
		}
	}

	if (type == BLACK_PAWN) {
		if (row == 7 && cur_game->board[6][col] == EMPTY_ENTRY &&
				cur_game->board[5][col] == EMPTY_ENTRY) {
			if (is_check_aux(valid_locs, cur_game, cur_piece, 5, col, i)) {
				i++;
			}
		}

		if (row >= 2 && cur_game->board[row - 1][col] == EMPTY_ENTRY) {
			if (is_check_aux(valid_locs, cur_game, cur_piece, row - 1, col, i)) {
				i++;
			}
		}
		// if board[i][j] is white
		if (row > 0 && col > 0 &&
				color_by_type(cur_game->board[row - 1][col - 1]) == 1) {
			if (is_check_aux(valid_locs, cur_game, cur_piece, row - 1, col - 1, i)) {
				i++;
			}
		}

		if (row > 0 && col < 7 &&
				color_by_type(cur_game->board[row - 1][col + 1]) == 1) {
			if (is_check_aux(valid_locs, cur_game, cur_piece, row - 1, col + 1, i)) {
				i++;
			}
		}
	}

	return valid_locs;
}

location* bishop_valid_moves(location* valid_locs, game* cur_game, piece* cur_piece) {
	int i = 0;
	int row = cur_piece->piece_location->row;
	int col = cur_piece->piece_location->column;
	int color = cur_piece->color;
	int next_row, next_col;

	//check upwards right
	next_row = row + 1;
	next_col = col + 1;
	while (next_row <= 8 && next_col <= 8 &&
			(cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		valid_locs[i].row = next_row;
		valid_locs[i].column = next_col;
		//check capturing
		if (check_capturing(cur_game->board[next_row][next_col], color)) {
				break;
		}
		i++;
		next_row++;
		next_col++;
	}

	//check upwards left
	next_row = row + 1;
	next_col = col - 1;
	while (next_row <= 8 && next_col >= 1 &&
			(cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			(color_by_type(cur_game->board[next_row][next_col]) != color))) {
		valid_locs[i].row = next_row;
		valid_locs[i].column = next_col;
		//check capturing
		if (check_capturing(cur_game->board[next_row][next_col], color)) {
			break;
		}
		i++;
		next_row++;
		next_col--;
	}

	//check downwards right
	next_row = row - 1;
	next_col = col + 1;
	while (next_row >= 1 && next_col <= 8 &&
			(cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		valid_locs[i].row = next_row;
		valid_locs[i].column = next_col;
		if (check_capturing(cur_game->board[next_row][next_col], color)) {
			break;
		}
		i++;
		next_row--;
		next_col++;
	}

	//check downwards left
	next_row = row - 1;
	next_col = col - 1;
	while (next_row >= 1 && next_col >= 1 &&
			(cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		valid_locs[i].row = next_row;
		valid_locs[i].column = next_col;
		if (check_capturing(cur_game->board[next_row][next_col], color)) {
			break;
		}
		i++;
		next_row--;
		next_col--;
	}
	return valid_locs;
}

location* rook_valid_moves(location* valid_locs, game* cur_game, piece* cur_piece) {
	int i = 0;
	int row = cur_piece->piece_location->row;
	int col = cur_piece->piece_location->column;
	int color = cur_piece->color;
	int next_row, next_col;

	//check upwards
	next_row = row + 1;
	next_col = col;
	while (next_row <= 8 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
			if (check_capturing(cur_game->board[next_row][next_col], color)) {
				break;
			}
		}
		next_row++;
	}

	//check downwards
		next_row = row - 1;
		next_col = col;
		while (next_row >= 1 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
				color_by_type(cur_game->board[next_row][next_col]) != color)) {
			if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
				i++;
				if (check_capturing(cur_game->board[next_row][next_col], color)) {
					break;
				}
			}
			next_row--;
		}

	//check right
		next_row = row;
		next_col = col + 1;
		while (next_col <= 7 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
				color_by_type(cur_game->board[next_row][next_col]) != color)) {
			if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
				i++;
				if (check_capturing(cur_game->board[next_row][next_col], color)) {
					break;
				}
			}
			next_col++;
		}

		//check left
		next_row = row;
		next_col = col - 1;
		while (next_col >= 0 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
				color_by_type(cur_game->board[next_row][next_col]) != color)) {
			if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
				i++;
				if (check_capturing(cur_game->board[next_row][next_col], color)) {
					break;
				}
			}
			next_col--;
		}
	return valid_locs;
}

location* knight_valid_moves(location* valid_locs, game* cur_game, piece* cur_piece) {
	printf("In knight valid moves\n"); //debug
	int i = 0;
	int row = cur_piece->piece_location->row;
	int col = cur_piece->piece_location->column;
	int color = cur_piece->color;
	int next_row, next_col;

	// check upward right (2 up, 1 right)
	next_row = row + 2;
	next_col = col + 1;
	if (row <= 7 && col <= 7 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
		}
	}

	// check upward left (2 up, 1 left)
	next_row = row + 2;
	next_col = col - 1;
	if (row <= 7 && col >= 0 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
		}
	}

	// check right upward (1 up, 2 right)
	next_row = row + 1;
	next_col = col + 2;
	if (row <= 7 && col <= 7 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
		}
	}

	// check left upward (1 up, 2 left)
	next_row = row + 1;
	next_col = col - 2;
	if (row <= 7 && col >= 0 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
		}
	}

	// check downward right (2 down, 1 right)
	next_row = row - 2;
	next_col = col + 1;
	if (row >= 0 && col <= 7 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
		}
	}

	// check downward left (2 down, 1 left)
	next_row = row - 2;
	next_col = col - 2;
	if (row >= 0 && col >= 0 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
		}
	}

	// check right downward (1 down, 2 right)
	next_row = row - 1;
	next_col = col + 2;
	if (row >= 0 && col <= 7 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
		}
	}

	// check left downward (1 down, 2 left)
	next_row = row - 1;
	next_col = col - 2;
	if (row >= 0 && col >= 0 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
		}
	}
	return valid_locs;
}
/* need to find a way to prevent the bishop moves from overriding the rook moves
location* queen_valid_moves(location* valid_locs, game* cur_game, piece* cur_piece) {
	bishop_valid_moves(valid_locs, cur_game, cur_piece);
	rook_valid_moves(valid_locs, cur_game, cur_piece);
	return valid_locs;
}
*/

/*
location* king_valid_moves(location* valid_locs, game* cur_game, piece* cur_piece) {
	printf("In king valid moves\n"); //debug
	int i = 0;
	char type = cur_piece->piece_type;
	int row = cur_piece->piece_location->row;
	int col = cur_piece->piece_location->column;
	int color = cur_piece->color;
	int next_row, next_col;

	return valid_locs;
}
*/

location* valid_moves(game* cur_game, piece* cur_piece) {
	char type = cur_piece->piece_type;
	location valid_locs[64];
	if (type == WHITE_PAWN || type == BLACK_PAWN) {
		return pawn_valid_moves(valid_locs, cur_game, cur_piece);
	}
	if (type == WHITE_BISHOP || type == BLACK_BISHOP) {
		return pawn_valid_moves(valid_locs, cur_game, cur_piece);
	}
	//tmp line 12.8.17
	return pawn_valid_moves(valid_locs, cur_game, cur_piece);
}

// given a move and a board says if the move is legal or not
bool is_valid_move(game* cur_game, move* cur_move) {
	int color;
	char source = cur_game->board[cur_move->source->row][(int)(cur_move->source->column-'A')];
	location* valid_locs; // list of all the valid location of the relevant piece

	// source is empty
	if (source == EMPTY_ENTRY){
		return false;
	}

	// update the color of the piece in the source
	if (source < 'z'){
		color = 1;
	}
	else{
		color = 0;
	}

	// source is enemy piece
	if (cur_game->current_turn - color != 0){
		return false;
	}

	// update valid_moves
	if (color == 1){
		for (int i=0; i<16; i++){
			if (cur_game->whites[i]->piece_type == source &&
					cur_game->whites[i]->piece_location->row == cur_move->source->row &&
					cur_game->whites[i]->piece_location->column == cur_move->source->column){
				printf("made it! (whites)\n");
				valid_locs = valid_moves(cur_game, cur_game->whites[i]);
				break;
			}
		}
	}

	if (color == 0){
		for (int i=0; i<16; i++){
			if (cur_game->blacks[i]->piece_type == source &&
					cur_game->blacks[i]->piece_location->row == cur_move->source->row &&
					cur_game->blacks[i]->piece_location->column == cur_move->source->column){
				printf("made it! (blacks)\n");
				valid_locs = valid_moves(cur_game, cur_game->blacks[i]);
				break;
			}
		}
	}

	// if cur_move->dest is one of the possible moves, return true
	for (int i=0; i<64; i++){
		if (valid_locs[i].row == cur_move->dest->row && valid_locs[i].column == cur_move->dest->column){
			return true;
		}
	}
	return false;
}

void move_piece(game* cur_game, move* cur_move, piece* cur_piece){
	// change the turn
	change_turn(cur_game);

	// update the piece location
	cur_piece->piece_location = cur_move->dest;

	// update the board
	cur_game->board[cur_move->source->row][(int)(cur_move->source->column - 'A')] = EMPTY_ENTRY;
	cur_game->board[cur_move->dest->row][(int)(cur_move->dest->column - 'A')] = cur_piece->piece_type;
}