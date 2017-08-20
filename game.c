/*
 * game.c
 *
 *  Created on: Aug 6, 2017
 *      Author: Gal
 */

#include "game.h"

/*
 * TODO
 * (1) need to change the size of the valid_moves array to 29 and initialize it to defuat locations (will make all checks much easier)
 * (2) in Is_valid_move there might be a memory leak in valid_locs (initalized as location* but needed to be location[64]
 */

piece* create_piece(){
	piece* piece = malloc(sizeof(piece));
	if (piece == NULL){
		free(piece);
		return NULL;
	}
	piece->alive = 1;
	piece->color = 0;
	piece->piece_location = (location*)(malloc(sizeof(location)));

	// default values
	piece->piece_location->row = -1;
	piece->piece_location->column = 'Z';
	if (piece->piece_location == NULL){
			free(piece->piece_location);
			free(piece);
			return NULL;
		}
	// initial it to EMPTY ENTRY
	piece->piece_type = EMPTY_ENTRY;
	return piece;
}

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

	newgame->whites = malloc(16 * sizeof(piece));
	newgame->blacks = malloc(16 * sizeof(piece));

	// initialize new pieces
	for (int i=0; i<16; i++){
		newgame->whites[i] = create_piece();
		if (newgame->whites[i] == NULL){
			free(newgame->whites[i]);
			free(newgame);
			return NULL;
		}
		newgame->blacks[i] = create_piece();
		if (newgame->blacks[i] == NULL){
			free(newgame->blacks[i]);
			free(newgame);
			return NULL;
		}
	}

	// initialize board //
	// initialize whites
	newgame->board[0][0] = WHITE_ROOK;
	newgame->board[0][1] = WHITE_KNIGHT;
	newgame->board[0][2] = WHITE_BISHOP;
	newgame->board[0][3] = WHITE_QUEEN;
	newgame->board[0][4] = WHITE_KING;
	newgame->board[0][5] = WHITE_KNIGHT;
	newgame->board[0][6] = WHITE_BISHOP;
	newgame->board[0][7] = WHITE_ROOK;
	for (int i=0; i<8;i++){
		newgame->board[1][i] = WHITE_PAWN;
	}

	// initialize blacks
	newgame->board[7][0] = BLACK_ROOK;
	newgame->board[7][1] = BLACK_KNIGHT;
	newgame->board[7][2] = BLACK_BISHOP;
	newgame->board[7][3] = BLACK_QUEEN;
	newgame->board[7][4] = BLACK_KING;
	newgame->board[7][5] = BLACK_KNIGHT;
	newgame->board[7][6] = BLACK_BISHOP;
	newgame->board[7][7] = BLACK_ROOK;
	for (int i=0; i<8;i++){
		newgame->board[6][i] = BLACK_PAWN;
	}


	for (int i=2; i<=5; i++){
		for (int j=0; j<=7;j++){
			newgame->board[i][j] = EMPTY_ENTRY;
		}
	}
	//initializing game.blacks and game.whites
	newgame->whites[0]->piece_type = WHITE_ROOK;
	newgame->whites[1]->piece_type = WHITE_KNIGHT;
	newgame->whites[2]->piece_type = WHITE_BISHOP;
	newgame->whites[3]->piece_type = WHITE_QUEEN;
	newgame->whites[4]->piece_type = WHITE_KING;
	newgame->whites[5]->piece_type = WHITE_KNIGHT;
	newgame->whites[6]->piece_type = WHITE_BISHOP;
	newgame->whites[7]->piece_type = WHITE_ROOK;
	newgame->whites[0]->alive = 1;
	for (int i=8; i<16;i++){
		newgame->whites[i]->piece_type = WHITE_PAWN;
	}

	for (int j=0; j < 16; j++) {
		newgame->whites[j]->alive = 1;
		newgame->whites[j]->piece_location->column = (char)(j) + 'A';
		if (newgame->whites[j]->piece_type != WHITE_PAWN) {
			newgame->whites[j]->piece_location->row = 'A';
		} else {
			newgame->whites[j]->piece_location->row = 'B';
		}
	}

	newgame->blacks[0]->piece_type = BLACK_ROOK;
	newgame->blacks[1]->piece_type = BLACK_KNIGHT;
	newgame->blacks[2]->piece_type = BLACK_BISHOP;
	newgame->blacks[3]->piece_type = BLACK_QUEEN;
	newgame->blacks[4]->piece_type = BLACK_KING;
	newgame->blacks[5]->piece_type = BLACK_KNIGHT;
	newgame->blacks[6]->piece_type = BLACK_BISHOP;
	newgame->blacks[7]->piece_type = BLACK_ROOK;
	for (int i=8; i<15;i++){
		newgame->blacks[i]->piece_type = BLACK_PAWN;
	}
	for (int i = 0; i < 16; i++) {
		newgame->blacks[i]->alive = 1;
		newgame->blacks[i]->color = 0;
		newgame->blacks[i]->piece_location->column = (char)(i) + 'A';
		if (newgame->blacks[i]->piece_type != BLACK_PAWN) {
			newgame->blacks[i]->piece_location->row = 'H';
		} else {
			newgame->blacks[i]->piece_location->row = 'G';
		}
	}

	return newgame;
}

//TODO -- need to update according to the changes in game create
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
	/* copying history
	for (int i=0; i<6; i++){
		copy->history[i] = cur_game->history[i];
	}
	*/

	copy->current_turn = cur_game->current_turn;
	copy->difficulty = cur_game->difficulty;
	copy->game_mode = cur_game->game_mode;
	copy->user_color = cur_game->user_color;
	return copy;
}

void game_destroy (game* cur_game) {
	//array_list_destroy(cur_game->history);
	free(cur_game->blacks);
	free(cur_game->whites);
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
	char col = cur_piece->piece_location->column;

	const location* king_loc;
	if (cur_piece->color == 1) {
		king_loc = cur_game->whites[4]->piece_location;
	} else {
		king_loc = cur_game->blacks[4]->piece_location;
	}
	if (type == WHITE_PAWN) {
		if (row == 2 && cur_game->board[4][(int)(col-'A')] == EMPTY_ENTRY) {
			valid_locs[i].row = 4;
			valid_locs[i].column = col;
			i++;
		}
		if (row <= 7 && cur_game->board[row + 1][(int)(col-'A')] == EMPTY_ENTRY) {
			valid_locs[i].row = row + 1;
			valid_locs[i].column = col;
			i++;
		}
		// if board[i][j] is a capital letter it's a black piece
		if (row <= 7 && col <= 'G' &&
				cur_game->board[row+1][(int)(col-'A')+1] <= 'Z' &&
				cur_game->board[row+1][(int)(col-'A')+1] >= 'A') {
			valid_locs[i].row = row +1;
			valid_locs[i].column = col +1;
			i++;
		}
		if (row <= 7 && col >= 'B' &&
				cur_game->board[row+1][(int)(col-'A')-1] <= 'Z' &&
				cur_game->board[row+1][(int)(col-'A')-1] >= 'A') {
			valid_locs[i].row = row +1;
			valid_locs[i].column = col - 1;
			i++;
		}
	}

	if (type == BLACK_PAWN) {
		if (row == 7 && cur_game->board[5][(int)(col-'A')] == EMPTY_ENTRY) {
			valid_locs[i].row = 5;
			valid_locs[i].column = col;
			i++;
		}
		if (row >= 2 && cur_game->board[row - 1][(int)(col-'A')] == EMPTY_ENTRY) {
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
	if (king_loc == NULL){
		printf("Gal added this line - king loc was not in use and it caused errors");
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
		valid_locs[i].row = next_row;
		valid_locs[i].column = next_col;
		if (check_capturing(cur_game->board[next_row][next_col], color)) {
			break;
		}
		i++;
		next_row++;
	}

	//check downwards
		next_row = row - 1;
		next_col = col;
		while (next_row >= 1 && (cur_game->board[next_row][next_col] == EMPTY_ENTRY ||
				color_by_type(cur_game->board[next_row][next_col]) != color)) {
			valid_locs[i].row = next_row;
			valid_locs[i].column = next_col;
			if (check_capturing(cur_game->board[next_row][next_col], color)) {
				break;
			}
			i++;
			next_row--;
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

void print_board(game* cur_game){

	if (cur_game == NULL)
		return ;

	for (int i=8; i>=1; i--){
		printf("%d|", i);
		for (int j=0; j<8 ; j++){
			printf("%c ", cur_game->board[i-1][j]);
		}
		printf("|\n");
	}
	printf("  -----------------\n  ");
	for (char c = 'A'; c <= 'H'; c++){
		printf("%c ", c);
	}
}

// change the turn
void change_turn(game* cur_game){
	if (cur_game->current_turn == 0){
		cur_game->current_turn = 1;
	}
	else{
		cur_game->current_turn = 0;
	}
}

// assuming that a move is legal - update the board, change the turn.
void move_piece(game* cur_game, move* cur_move, piece* cur_piece){
	// change the turn
	change_turn(cur_game);

	// update the piece location
	cur_piece->piece_location = cur_move->dest;

	// update the board
	cur_game->board[cur_move->source->row][(int)(cur_move->source->column - 'A')] = EMPTY_ENTRY;
	cur_game->board[cur_move->dest->row][(int)(cur_move->dest->column - 'A')] = cur_piece->piece_type;
}

// given a move and a board says if the move is legal or not
bool is_valid_move(game* cur_game, move* cur_move){
	int color;
	char source = cur_game->board[cur_move->source->row][(int)(cur_move->source->column-'A')];
	location* valid_locs; // list of all the valid location of the relevant piece

	printf("source is: %c\n", source);

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

	printf("color is: %d\n", color);
	printf("current_turn: %d\n", cur_game->current_turn);

	// source is enemy piece
	if (cur_game->current_turn - color != 0){
		return false;
	}

	// update valid_moves
	if (color == 1){
		for (int i=0; i<16; i++){
			if (cur_game->whites[i]->piece_type == source){
				valid_locs = valid_moves(cur_game, cur_game->whites[i]);
				break;
			}
		}
	}

	if (color == 0){
		for (int i=0; i<16; i++){
			if (cur_game->blacks[i]->piece_type == source){
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

bool check_diagonals(game* cur_game, const location* king_loc, location* enemy_loc){
	// up right diagonal
	for (int i=0; i<8; i++){

		if ((enemy_loc->row + i == king_loc->row) && (enemy_loc->column + i == king_loc->column)){
			return true;
		}

		if (enemy_loc->row + i > 8 || enemy_loc->column + i > 'H'){
			continue;
		}

		if (cur_game->board[enemy_loc->row + i][enemy_loc->column + i - 'A'] != EMPTY_ENTRY){
			continue;
		}
	}

	// up left diagonal
	for (int i=0; i<8; i++){
		if (enemy_loc->row - i == king_loc->row && enemy_loc->column+ i == king_loc->column){
			return true;
		}
		if (enemy_loc->row - i < 1 || enemy_loc->column + i > 'H'){
			continue;
		}
		if (cur_game->board[enemy_loc->row - i][enemy_loc->column + i - 'A'] != EMPTY_ENTRY){
			continue;
		}
	}

	// down left diagonal
	for (int i=0; i<8; i++){
		if (enemy_loc->row - i == king_loc->row && enemy_loc->column - i == king_loc->column){
			return true;
		}
		if (enemy_loc->row - i < 1 || enemy_loc->column- i < 'A'){
			continue;
		}
		if (cur_game->board[enemy_loc->row - i][enemy_loc->column - i - 'A'] != EMPTY_ENTRY){
			continue;
		}
	}

	// down right diagonal
	for (int i=0; i<8; i++){
		if (enemy_loc->row + i == king_loc->row && enemy_loc->column - i == king_loc->column){
			return true;
		}
		if (enemy_loc->row + i < 8 || enemy_loc->column- i > 'A'){
			continue;
		}
		if (cur_game->board[enemy_loc->row + i][enemy_loc->column - i - 'A'] != EMPTY_ENTRY){
			continue;
		}
	}
	return false;
}

bool check_parallels(game* cur_game, const location* king_loc, location* enemy_loc){
	// up
	for (char i=0; i<8; i++){
		if (enemy_loc->column+ i > 'H' || cur_game->board[enemy_loc->row][(int)(enemy_loc->column + i - 'A')] != EMPTY_ENTRY){
			continue;
		}
		if (enemy_loc->column+ i == king_loc->column && enemy_loc->row  == king_loc->row){
			return true;
		}
	}

	// down
	for (char i=0; i<8; i++){
		if (enemy_loc->column- i < 'A' || cur_game->board[enemy_loc->row][(int)(enemy_loc->column - i - 'A')] != EMPTY_ENTRY){
			continue;
		}
		if (enemy_loc->column- i == king_loc->column&& enemy_loc->row  == king_loc->row){
			return true;
		}
	}

	// right
	for (int i=0; i<8; i++){
		if (enemy_loc->row + i > 8 || cur_game->board[enemy_loc->row + i][(int)(enemy_loc->column - 'A')] != EMPTY_ENTRY){
			continue;
		}
		if (enemy_loc->row + i == king_loc->row && enemy_loc->column == king_loc->column){
			return true;
		}
	}

	// left
	for (int i=0; i<8; i++){
		if (enemy_loc->row- i < 1 || cur_game->board[enemy_loc->row - i][(int)(enemy_loc->column - 'A')] != EMPTY_ENTRY){
			continue;
		}
		if (enemy_loc->row - i == king_loc->row && enemy_loc->column == king_loc->column){
			return true;
		}
	}
	return false;
}

bool is_check(game* cur_game, const location* king_loc, const piece* enemy_locs){

	if (cur_game == NULL){
		return false;
	}

	// finds the location of the white king
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
			if (check_diagonals(cur_game, king_loc, enemy_locs[i].piece_location) == true){
				return true;
			}
		}

		// rook
		if (enemy_locs[i].piece_type == BLACK_ROOK || enemy_locs[i].piece_type == WHITE_ROOK){
			if (check_parallels(cur_game, king_loc, enemy_locs[i].piece_location) == true){
				return true;
			}
		}

		// queen
		if (enemy_locs[i].piece_type == BLACK_QUEEN || enemy_locs[i].piece_type == WHITE_QUEEN){
			if ((check_parallels(cur_game, king_loc, enemy_locs[i].piece_location) == true) ||
				(check_diagonals(cur_game, king_loc, enemy_locs[i].piece_location) == true)){
				return true;
			}
		}

		// king
		if (enemy_locs[i].piece_type == BLACK_KING || enemy_locs[i].piece_type == WHITE_KING){
			if (((king_loc->row - (enemy_locs[i].piece_location->row)) < 1 && (king_loc->row - (enemy_locs[i].piece_location->row)) > 0) &&
				((king_loc->column - (enemy_locs[i].piece_location->column)) < 'A' && (king_loc->column - (enemy_locs[i].piece_location->column)) >= 'A')){
				return true;
			}
		}
	}
	return false;
}
