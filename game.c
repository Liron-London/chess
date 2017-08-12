/*
 * game.c
 *
 *  Created on: Aug 6, 2017
 *      Author: Gal
 */

#include "game.h"

game* game_create() {
	game* newgame = (game*)malloc(sizeof(game));
	if (newgame == NULL) {
		free(newgame);
		return NULL;
	}
	newgame->game_mode = 1;
	newgame->difficulty = 2;
	newgame->user_color = 1;
	newgame->current_turn = 1;
	return newgame;
}

game* game_copy(game* cur_game) {
	if (cur_game == NULL)
		return NULL;
	game* copy = game_create();
	if (copy == NULL) {
		free(copy);
		return NULL;
	}
	// copying board
	for (int i=0; i<8; i++){
		for (int j=0; j<8; j++){
			copy->board[i][j] = cur_game->board[i][j];
		}
	}
	// copying history
	for (int i=0; i<6; i++){
		copy->history[i] = cur_game->history[i];
	}

	copy->current_turn = cur_game->current_turn;
	copy->difficulty = cur_game->difficulty;
	copy->game_mode = cur_game->game_mode;
	copy->user_color = cur_game->user_color;
	return copy;
}

void game_destroy (game* cur_game) {
	free(cur_game);
}

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

location* pawn_valid_moves(	location* valid_locs, game* cur_game, piece* cur_piece) {
	int i = 0;
	char type = cur_piece->piece_type;
	int row = cur_piece->piece_location->row;
	int col = cur_piece->piece_location->column;
	if (type == WHITE_PAWN) {
		if (row == 2 && cur_game->board[4][col] == EMPTY_ENTRY) {
			valid_locs[i].row = 4;
			valid_locs[i].column = col;
			i++;
		}
		if (row <= 7 && cur_game->board[row + 1][col] == EMPTY_ENTRY) {
			valid_locs[i].row = row + 1;
			valid_locs[i].column = col;
			i++;
		}
		// if board[i][j] is a capital letter it's a black piece
		if (row <= 7 && col <= 'G' &&
				cur_game->board[row+1][col+1] <= 'Z' &&
				cur_game->board[row+1][col+1] >= 'A') {
			valid_locs[i].row = row +1;
			valid_locs[i].column = col +1;
			i++;
		}
		if (row <= 7 && col >= 'B' &&
				cur_game->board[row+1][col-1] <= 'Z' &&
				cur_game->board[row+1][col-1] >= 'A') {
			valid_locs[i].row = row +1;
			valid_locs[i].column = col - 1;
			i++;
		}
	}

	if (type == BLACK_PAWN) {
		if (row == 7 && cur_game->board[5][col] == EMPTY_ENTRY) {
			valid_locs[i].row = 5;
			valid_locs[i].column = col;
			i++;
		}
		if (row >= 2 && cur_game->board[row - 1][col] == EMPTY_ENTRY) {
			valid_locs[i].row = row - 1;
			valid_locs[i].column = col;
			i++;
		}
		// if board[i][j] is a lowercase character it's a white piece
		if (row >= 2 && col >= 'B' &&
				cur_game->board[row - 1][col - 1] <= 'z' &&
				cur_game->board[row - 1][col - 1] >= 'a') {
			valid_locs[i].row = row -1;
			valid_locs[i].column = col -1;
			i++;
		}
		if (row >= 2 && col <= 'G' &&
				cur_game->board[row + 1][col - 1] <= 'z' &&
				cur_game->board[row + 1][col - 1] >= 'a') {
			valid_locs[i].row = row +1;
			valid_locs[i].column = col - 1;
			i++;
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
			cur_game->board[next_row][next_col] == EMPTY_ENTRY) {
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
			cur_game->board[next_row][next_col] == EMPTY_ENTRY) {
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
			cur_game->board[next_row][next_col] == EMPTY_ENTRY) {
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

//void set_move(game* cur_game, piece* cur_piece, location* dst_location) {
//}

void print_board(game* cur_game){

	if (cur_game == NULL)
		return ;

	for (int i=8; i>0; i--){
		printf("  %d|", i);
		for (int j=0; j<8 ; j++){
			printf("%c ", cur_game->board[i][j]);
		}
		printf("|\n");
	}
	printf(" -----------------\n   ");
	for (char c = 'A'; c <= 'H'; c++){
		printf("%c ", c);
	}
}

bool check_diagonals(game* cur_game, location* king_loc, location* enemy_loc){
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
		if (enemy_loc->row - i == king_loc->row && enemy_loc->column+ i == king_loc->column){
			return true;
		}
	}

	// down left diagonal
	for (int i=0; i<8; i++){
		if (enemy_loc->row - i < 0 || enemy_loc->column- i < 0){
			continue;
		}
		if (enemy_loc->row - i == king_loc->row && enemy_loc->column- i == king_loc->column){
			return true;
		}
	}

	// down right diagonal
	for (int i=0; i<8; i++){
		if (enemy_loc->row + i < 8 || enemy_loc->column- i > 0){
			continue;
		}
		if (enemy_loc->row + i == king_loc->row && enemy_loc->column- i == king_loc->column){
			return true;
		}
	}
	return false;
}

bool check_parallels(game* cur_game, location* king_loc, location* enemy_loc){
	// up
	for (int i=0; i<8; i++){
		if (enemy_loc->column+ i > 8 || cur_game->board[enemy_loc->row][enemy_loc->column + i] != EMPTY_ENTRY){
			continue;
		}
		if (enemy_loc->column+ i == king_loc->column && enemy_loc->row  == king_loc->row){
			return true;
		}
	}

	// down
	for (int i=0; i<8; i++){
		if (enemy_loc->column- i < 0 || cur_game->board[enemy_loc->row][enemy_loc->column - i] != EMPTY_ENTRY){
			continue;
		}
		if (enemy_loc->column- i == king_loc->column&& enemy_loc->row  == king_loc->row){
			return true;
		}
	}

	// right
	for (char i=0; i<8; i++){
		if (enemy_loc->row + i > 'H' || cur_game->board[enemy_loc->row + i][enemy_loc->column] != EMPTY_ENTRY){
			continue;
		}
		if (enemy_loc->row + i == king_loc->row && enemy_loc->column == king_loc->column){
			return true;
		}
	}

	// left
	for (char i=0; i<8; i++){
		if (enemy_loc->row - i < 'A' || cur_game->board[enemy_loc->row - i][enemy_loc->column] != EMPTY_ENTRY){
			continue;
		}
		if (enemy_loc->row - i == king_loc->row && enemy_loc->column == king_loc->column){
			return true;
		}
	}
	return false;
}

bool is_check(game* cur_game, const piece* king, const piece* enemy_locs){

	if (cur_game == NULL){
		return false;
	}

	// finds the location of the white king
	location* king_loc = king->piece_location;
	location* enemy_loc;

	for (int i=0; i<16; i++){
		// putting location into variable for readability
		enemy_loc = enemy_locs[i].piece_location;

		// black pawn
		if (enemy_locs[i].piece_type == BLACK_PAWN){
			if ((enemy_loc->column = (king_loc->column) + 1) &&
					((enemy_loc->row = (king_loc->row) + 1) ||(enemy_loc->row = (king_loc->row) - 1))){
				return true;
			}
		}

		// white pawn
		if (enemy_locs[i].piece_type == BLACK_PAWN){
			if ((enemy_loc->column = (king_loc->column) - 1) &&
					((enemy_loc->row = (king_loc->row) + 1) ||(enemy_loc->row = (king_loc->row) - 1))){
				return true;
			}
		}

		// knight
		if (enemy_locs[i].piece_type == BLACK_KNIGHT || enemy_locs[i].piece_type == WHITE_KNIGHT){
			if (((enemy_loc->column = (king_loc->column) + 2) && ((enemy_loc->row = (king_loc->row) + 1) ||(enemy_loc->row = (king_loc->row) - 1))) ||
				((enemy_loc->column = (king_loc->column) - 2) && ((enemy_loc->row = (king_loc->row) + 1) ||(enemy_loc->row = (king_loc->row) - 1)))||
				((enemy_loc->row = (king_loc->row) + 2) && ((enemy_loc->column = (king_loc->column) + 1) ||(enemy_loc->column = (king_loc->column) - 1)))||
				((enemy_loc->row = (king_loc->row) - 2) && ((enemy_loc->column = (king_loc->column) + 1) ||(enemy_loc->column = (king_loc->column) - 1)))){
				return true;
			}
		}

		// bishop
		if (enemy_locs[i].piece_type == BLACK_BISHOP || enemy_locs[i].piece_type == WHITE_BISHOP){
			if (check_diagonals(cur_game, king->piece_location, enemy_locs[i].piece_location) == true){
				return true;
			}
		}

		// rook
		if (enemy_locs[i].piece_type == BLACK_ROOK || enemy_locs[i].piece_type == WHITE_ROOK){
			if (check_parallels(cur_game, king->piece_location, enemy_locs[i].piece_location) == true){
				return true;
			}
		}

		// queen
		if (enemy_locs[i].piece_type == BLACK_QUEEN || enemy_locs[i].piece_type == WHITE_QUEEN){
			if ((check_parallels(cur_game, king->piece_location, enemy_locs[i].piece_location) == true) ||
				(check_diagonals(cur_game, king->piece_location, enemy_locs[i].piece_location) == true)){
				return true;
			}
		}

		// king
		if (enemy_locs[i].piece_type == BLACK_KING || enemy_locs[i].piece_type == WHITE_KING){
			if (((king.piece_location->row - (enemy_locs[i].piece_location->row)) <= A && (king.piece_location->row - (enemy_locs[i].piece_location->row)) >= 'A') &&
				((king.piece_location->column - (enemy_locs[i].piece_location->column)) < 1 && (king.piece_location->column - (enemy_locs[i].piece_location->column)) > -1)){
				return true;
			}
		}
	}
	return false;
}
