/*
 * moves.c
 *
 *  Created on: Aug 23, 2017
 *      Author: lironl
 */
#include "moves.h"
#include "debug.h"

// get the color of a piece according to its type
int color_by_type(char piece_type) {
	if ('A' <= piece_type && piece_type <= 'Z') {
		return 0;
	} else if ('a' <= piece_type && piece_type <= 'z') {
		return 1;
	}
	return 2;
}

bool check_capturing(char piece_in_next_loc, int color) {
	if (piece_in_next_loc != EMPTY_ENTRY &&
			color_by_type(piece_in_next_loc) != color) {
		return true;
	}
	return false;
}

move* create_move() {
	move* new_move = malloc(sizeof(move));
	if (new_move == NULL) {
		free(new_move);
		return NULL;
	}
	new_move->source = create_location();
	if (new_move->source == NULL) {
		free(new_move->source);
		free(new_move);
		return NULL;
	}
	new_move->dest = create_location();
	if (new_move->dest == NULL) {
		destroy_move(new_move);
		return NULL;
	}
	return new_move;
}

move* copy_move(move* cur_move){
	move* move_copy = create_move();
	move_copy->dest->row = cur_move->dest->row;
	move_copy->dest->column = cur_move->dest->column;
	move_copy->source->row = cur_move->source->row;
	move_copy->source->column = cur_move->source->column;
	return move_copy;

}

void destroy_move(move* old_move) {
	destroy_location(old_move->dest);
	destroy_location(old_move->source);
	free(old_move);
}

// update valid_locs with next_row, next_col in case the move is a valid move
bool is_check_aux(location** valid_locs, game* cur_game, piece* cur_piece,
		int next_row, int next_col, int index) {
	bool valid_move = false;

	game* tmp_game = game_copy(cur_game);
	move* tmp_move = create_move();
	piece* tmp_piece;

	if (current_turn_color(cur_game) == 0){
		for (int i=0; i<16; i++){
			if (tmp_game->whites[i]->piece_location->row == cur_piece->piece_location->row &&
				tmp_game->whites[i]->piece_location->column == cur_piece->piece_location->column && tmp_game->whites[i]->alive==1){
				tmp_piece = tmp_game->whites[i];
			}
		}
	}

	if (current_turn_color(cur_game) == 1){
		for (int i=0; i<16; i++){
			if (tmp_game->blacks[i]->piece_location->row == cur_piece->piece_location->row &&
				tmp_game->blacks[i]->piece_location->column == cur_piece->piece_location->column && tmp_game->blacks[i]->alive==1){
					tmp_piece = tmp_game->blacks[i];
			}
		}
	}

	// source_location is always the piece location
	tmp_move->source->row = tmp_piece->piece_location->row;
	tmp_move->source->column = tmp_piece->piece_location->column;

	tmp_move->dest->row = next_row;
	tmp_move->dest->column = next_col;

	move_piece(tmp_game, tmp_move, tmp_piece);

	if (is_check(tmp_game) == false) {
		valid_locs[index]->row = next_row;
		valid_locs[index]->column = next_col;
		valid_move = true;
	}

	// free variables
	destroy_move(tmp_move);
	game_destroy(tmp_game);
	return valid_move;
}

// checks all possible valid moves for pawn
void pawn_valid_moves(location** valid_locs, game* cur_game, piece* cur_piece) {
	int i = 0;
	char type = cur_piece->piece_type;
	int row = cur_piece->piece_location->row;
	int col = cur_piece->piece_location->column;

	int color = current_turn_color(cur_game);

	if (type == WHITE_PAWN && color == 0) {
		if (row == 1 && cur_game->board[2][col] == EMPTY_ENTRY &&
				cur_game->board[3][col] == EMPTY_ENTRY) {

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
				color_by_type(cur_game->board[row + 1][col - 1]) == 0) {
			if (is_check_aux(valid_locs, cur_game, cur_piece, row + 1, col - 1, i)) {
				i++;
			}
		}
	}

	if (type == BLACK_PAWN && color == 1) {
		if (row == 6 && cur_game->board[5][col] == EMPTY_ENTRY &&
				cur_game->board[4][col] == EMPTY_ENTRY) {
			if (is_check_aux(valid_locs, cur_game, cur_piece, 4, col, i)) {
				i++;
			}
		}

		if (row >= 1 && cur_game->board[row - 1][col] == EMPTY_ENTRY) {
			if (is_check_aux(valid_locs, cur_game, cur_piece, row - 1, col, i)) {
				i++;
			}
		}
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
}

// check if a board has valid moves - used to determine if there is a mate or a tie
bool has_valid_moves(game* cur_game){
	piece** pieces;
	location** valid_locs = malloc(64*sizeof(location*));
	for (int i=0; i<64; i++){
		valid_locs[i] = create_location();
	}

	int color = (cur_game->current_turn + cur_game->user_color)%2;

	if (color == 0){
		pieces = cur_game->whites;
	}
	else{
		pieces = cur_game->blacks;
	}

	for (int i=0; i<16; i++){
		if (pieces[i]->alive == true){
			valid_moves(valid_locs, cur_game,pieces[i]);
			// if valid_locs[0] is not null it means there is at least one valid move
			if (valid_locs[0]->row != -1){
				for (int i=0; i<64;i++){
					free(valid_locs[i]);
				}
				free(valid_locs);
				return true;
			}
		}
	}
	// there are no valid moves, return true
	for (int i=0; i<64;i++){
		free(valid_locs[i]);
	}
	free(valid_locs);
	return false;
}

// checks all valid moves for a bishop
void bishop_valid_moves(location** valid_locs, game* cur_game, piece* cur_piece) {
	int i = 0;
	int row = cur_piece->piece_location->row;
	int col = cur_piece->piece_location->column;
	int color = cur_piece->color;
	int next_row, next_col;

	//check upwards right
	next_row = row + 1;
	next_col = col + 1;
	while (next_row <= 7 && next_col <= 7 &&
			(cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		//check capturing
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
			if (check_capturing(cur_game->board[next_row][next_col], color)) {
				break;
			}
		}
		next_row++;
		next_col++;
	}

	//check upwards left
	next_row = row + 1;
	next_col = col - 1;
	while (next_row <= 7 && next_col >= 0 &&
			(cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			(color_by_type(cur_game->board[next_row][next_col]) != color))) {
		//check capturing
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
			if (check_capturing(cur_game->board[next_row][next_col], color)) {
				break;
			}
		}
		next_row++;
		next_col--;
	}

	//check downwards right
	next_row = row - 1;
	next_col = col + 1;
	while (next_row >= 0 && next_col <= 7 &&
			(cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
			if (check_capturing(cur_game->board[next_row][next_col], color)) {
				break;
			}
		}
		next_row--;
		next_col++;
	}

	//check downwards left
	next_row = row - 1;
	next_col = col - 1;
	while (next_row >= 0 && next_col >= 0 &&
			(cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
			if (check_capturing(cur_game->board[next_row][next_col], color)) {
				break;
			}
		}
		next_row--;
		next_col--;
	}
}

// check all valid moves for rook
void rook_valid_moves(location** valid_locs, game* cur_game, piece* cur_piece) {
	int i = 0;
	int row = cur_piece->piece_location->row;
	int col = cur_piece->piece_location->column;
	int color = cur_piece->color;
	int next_row, next_col;

	//check upwards
	next_row = row + 1;
	next_col = col;
	while (next_row <= 7 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
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
		while (next_row >= 0 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
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
}

// check all valid moves for knight
void knight_valid_moves(location** valid_locs, game* cur_game, piece* cur_piece) {
	int i = 0;
	int row = cur_piece->piece_location->row;
	int col = cur_piece->piece_location->column;
	int color = cur_piece->color;
	int next_row, next_col;

	// check upward right (2 up, 1 right)
	next_row = row + 2;
	next_col = col + 1;
	if (next_row <= 7 && next_col <= 7 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
		}
	}

	// check upward left (2 up, 1 left)
	next_row = row + 2;
	next_col = col - 1;
	if (next_row <= 7 && next_col >= 0 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
		}
	}

	// check right upward (1 up, 2 right)
	next_row = row + 1;
	next_col = col + 2;
	if (next_row <= 7 && next_col <= 7 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
		}
	}

	// check left upward (1 up, 2 left)
	next_row = row + 1;
	next_col = col - 2;
	if (next_row <= 7 && next_col >= 0 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
		}
	}

	// check downward right (2 down, 1 right)
	next_row = row - 2;
	next_col = col + 1;
	if (next_row >= 0 && next_col <= 7 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
		}
	}

	// check downward left (2 down, 1 left)
	next_row = row - 2;
	next_col = col - 1;
	if (next_row >= 0 && next_col >= 0 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
		}
	}

	// check right downward (1 down, 2 right)
	next_row = row - 1;
	next_col = col + 2;
	if (next_row >= 0 && next_col <= 7 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
		}
	}

	// check left downward (1 down, 2 left)
	next_row = row - 1;
	next_col = col - 2;
	if (next_row >= 0 && next_col >= 0 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color)) {
		if (is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
		}
	}
}

// calculate all valid moves for a queen using parallel and diagonal checks
void queen_valid_moves(location** valid_locs, game* cur_game, piece* cur_piece) {
	bishop_valid_moves(valid_locs, cur_game, cur_piece);
	location** new_ptr_to_valid_locs;

	for (int i = 0; i < 64; i++) {
		if (valid_locs[i]->row == -1 && valid_locs[i]->column == -1) {
			new_ptr_to_valid_locs = &valid_locs[i];
			break ;
		}
	}
	rook_valid_moves(new_ptr_to_valid_locs, cur_game, cur_piece);
}


// check king valid moves
void king_valid_moves(location** valid_locs, game* cur_game, piece* cur_piece) {
	int i = 0;
	int row = cur_piece->piece_location->row;
	int col = cur_piece->piece_location->column;
	int color = cur_piece->color;
	int next_row, next_col;

	//check up
	next_row = row + 1;
	next_col = col;
	if (next_row <= 7 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color) &&
			is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
	}

	//check down
	next_row = row - 1;
	next_col = col;
	if (next_row >= 0 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color) &&
			is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
			i++;
	}

	//check right
	next_row = row;
	next_col = col + 1;
	if (next_col <= 7 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color) &&
			is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
		i++;
	}

	//check left
	next_row = row;
	next_col = col - 1;
	if (next_col >= 0 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color) &&
			is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
		i++;
	}

	//check up-right
	next_row = row + 1;
	next_col = col + 1;
	if (next_row <= 7 && next_col <= 7 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color) &&
			is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
		i++;
	}

	//check up-left
	next_row = row + 1;
	next_col = col - 1;
	if (next_row <= 7 && next_col >= 0 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color) &&
			is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
		i++;
	}

	//check down-right
	next_row = row - 1;
	next_col = col + 1;
	if (next_row >= 0 && next_col <= 7 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color) &&
			is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
		i++;
	}

	//check down-left
	next_row = row - 1;
	next_col = col - 1;
	if (next_row >= 0 && next_col >= 0 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
			color_by_type(cur_game->board[next_row][next_col]) != color) &&
			is_check_aux(valid_locs, cur_game, cur_piece, next_row, next_col, i)) {
		i++;
	}
}

// update valid_locs for all possible valid moves on the board
void valid_moves(location** valid_locs, game* cur_game, piece* cur_piece) {
	char type = cur_piece->piece_type;

	if (type == WHITE_PAWN || type == BLACK_PAWN) {
		pawn_valid_moves(valid_locs, cur_game, cur_piece);
	}
	if (type == WHITE_BISHOP || type == BLACK_BISHOP) {
		bishop_valid_moves(valid_locs, cur_game, cur_piece);
	}
	if (type == WHITE_ROOK || type == BLACK_ROOK) {
		rook_valid_moves(valid_locs, cur_game, cur_piece);
	}
	if (type == WHITE_KNIGHT || type == BLACK_KNIGHT) {
		knight_valid_moves(valid_locs, cur_game, cur_piece);
	}
	if (type == WHITE_QUEEN || type == BLACK_QUEEN) {
		queen_valid_moves(valid_locs, cur_game, cur_piece);
	}
	if (type == WHITE_KING || type == BLACK_KING){
		king_valid_moves(valid_locs, cur_game, cur_piece);
	}
}

void announce_invalid_move() {
	printf("Illegal move\n");
}

void announce_illegal_move_src() {
	printf("The specified position does not contain your piece\n");
}

void announce_illegal_place_on_board(){
	printf("Invalid position on the board\n");
}

void destroy_valid_locs(location** valid_locs) {
	for (int i = 0; i < 64; i++) {
		destroy_location(valid_locs[i]);
	}
	free(valid_locs);
}

// given a move and a board says if the move is legal or not
bool is_valid_move(game* cur_game, move* cur_move) {
	int color;
	char source = cur_game->board[cur_move->source->row][cur_move->source->column];


	location** valid_locs = calloc(64, sizeof(location*)); // list of all the valid location of the relevant piece
	for (int i=0; i<64; i++){
		valid_locs[i] = create_location();
	}

	if (cur_move->source->row < 0 || cur_move->source->row > 7 || cur_move->dest->row < 0 || cur_move->dest->row > 7 ||
			cur_move->source->column < 0 || cur_move->source->column > 7 || cur_move->dest->column < 0 || cur_move->dest->column > 7){
		announce_illegal_place_on_board();
		destroy_valid_locs(valid_locs);
		return false;
	}

	color = (cur_game->current_turn + cur_game->user_color + 1)%2;
	if (source == EMPTY_ENTRY ||
			color_by_type(cur_game->board[cur_move->source->row][cur_move->source->column]) != color) {
		announce_illegal_move_src();
		destroy_valid_locs(valid_locs);
		return false;
	}

	// update valid_moves
	if (color == 1){
		for (int i=0; i<16; i++){
			if (cur_game->whites[i]->piece_type == source && cur_game->whites[i]->alive &&
					cur_game->whites[i]->piece_location->row == cur_move->source->row &&
					cur_game->whites[i]->piece_location->column == cur_move->source->column){
				//DEBUG("made it! (whites)\n");
				valid_moves(valid_locs, cur_game, cur_game->whites[i]);
				break;
			}
		}
	}

	if (color == 0){
		for (int i=0; i<16; i++){
			if (cur_game->blacks[i]->piece_type == source && cur_game->blacks[i]->alive &&
					cur_game->blacks[i]->piece_location->row == cur_move->source->row &&
					cur_game->blacks[i]->piece_location->column == cur_move->source->column){
				//DEBUG("made it! (blacks)\n");
				valid_moves(valid_locs, cur_game, cur_game->blacks[i]);

				break;
			}
		}
	}

	// if cur_move->dest is one of the possible moves, return true
	for (int i=0; i<64; i++){
		if (valid_locs[i]->row == cur_move->dest->row && valid_locs[i]->column == cur_move->dest->column){
			destroy_valid_locs(valid_locs);
			return true;
		}
	}
	destroy_valid_locs(valid_locs);
	announce_invalid_move();
	return false;
}

void move_piece(game* cur_game, move* cur_move, piece* cur_piece){
	change_turn(cur_game);

	cur_piece->piece_location->row = cur_move->dest->row;
	cur_piece->piece_location->column = cur_move->dest->column;

	// checks if a piece should be killed and kill it if needed
	if (cur_game->board[cur_move->dest->row][cur_move->dest->column] != EMPTY_ENTRY){
		piece* dead_piece = location_to_piece(cur_game, cur_move->dest);
		dead_piece->alive = 0;
	}

	// update the board
	cur_game->board[cur_move->source->row][cur_move->source->column] = EMPTY_ENTRY;
	cur_game->board[cur_move->dest->row][cur_move->dest->column] = cur_piece->piece_type;
}
