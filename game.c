/*
 * game.c
 *
 *  Created on: Aug 6, 2017
 *      Author: Gal
 */

#include "game.h"
#include "debug.h"

// returns the turn of the current player
int current_turn_color(game* game) {
	return (game->current_turn + game->user_color)%2;
}

// return the pieces located in a specific location on the board
piece* location_to_piece(game* cur_game, location* loc){
	char type = cur_game->board[loc->row][loc->column];
	if (type == EMPTY_ENTRY){
		return NULL;
	}

	// check if black or white
	if (type > 'a'){
		for (int i=0; i<16;i++){
			if (cur_game->whites[i]->piece_location->row == loc->row &&
					cur_game->whites[i]->piece_location->column == loc->column && cur_game->whites[i]->alive == 1){
				return cur_game->whites[i];
			}
		}
	}

	else{
		for (int i=0; i<16;i++){
			if (cur_game->blacks[i]->piece_location->row == loc->row && cur_game->blacks[i]->piece_location->column == loc->column
					&& cur_game->blacks[i]->alive == 1){
				return cur_game->blacks[i];
			}
		}
	}
	return NULL;
}

location* create_location(){
	location* loc = malloc(sizeof(location));
	loc->row = -1;
	loc->column = -1;
	return loc;
}

location* copy_location(location* loc){
	location* new_loc = create_location();
	new_loc->row = loc->row;
	new_loc->column = loc->column;
	return new_loc;
}

void destroy_location(location* loc){
	free(loc);
}


piece* create_piece() {
	piece* new_piece = malloc(sizeof(piece));
	if (new_piece == NULL) {
		free(new_piece);
		return NULL;
	}
	new_piece->alive = 1;
	new_piece->color = 0;
	new_piece->piece_location = create_location();
	if (new_piece->piece_location == NULL){
			destroy_location(new_piece->piece_location);
			free(new_piece);
			return NULL;
		}
	// initial it to EMPTY ENTRY
	new_piece->piece_type = EMPTY_ENTRY;
	return new_piece;
}

void destroy_piece(piece* cur_piece){
	free(cur_piece->piece_location);
	free(cur_piece);
}

piece* copy_piece(piece* cur_piece){
	piece* new_piece = create_piece();
	new_piece->alive = cur_piece->alive;
	new_piece->color = cur_piece->color;
	new_piece->piece_location->row = cur_piece->piece_location->row;
	new_piece->piece_location->column = cur_piece->piece_location->column;
	new_piece->piece_type = cur_piece->piece_type;
	return new_piece;
}


game* game_create() {
	game* newgame = malloc(sizeof(game));
	if (newgame == NULL) {
		free(newgame);
		return NULL;
	}
	newgame->game_mode = 1;
	newgame->difficulty = 2;
	newgame->user_color = 1;
	newgame->current_turn = 1;

	newgame->whites =(piece**) malloc(16 * sizeof(piece*));
	if (newgame->whites == NULL){
		free(newgame->whites);
		free(newgame);
		return NULL;
	}

	newgame->blacks =(piece**) malloc(16 * sizeof(piece*));
	if (newgame->whites == NULL){
		free(newgame->blacks);
		free(newgame->whites);
		free(newgame);
		return NULL;
	}

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
	newgame->board[0][5] = WHITE_BISHOP;
	newgame->board[0][6] = WHITE_KNIGHT;
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
	newgame->board[7][5] = BLACK_BISHOP;
	newgame->board[7][6] = BLACK_KNIGHT;
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
	newgame->whites[5]->piece_type = WHITE_BISHOP;
	newgame->whites[6]->piece_type = WHITE_KNIGHT;
	newgame->whites[7]->piece_type = WHITE_ROOK;
	for (int i=8; i<16;i++){
		newgame->whites[i]->piece_type = WHITE_PAWN;
	}

	for (int j=0; j < 16; j++) {
		newgame->whites[j]->alive = 1;
		newgame->whites[j]->color = 1;
		newgame->whites[j]->piece_location->column = j%8;
		if (newgame->whites[j]->piece_type != WHITE_PAWN) {
			newgame->whites[j]->piece_location->row = 0;
		} else {
			newgame->whites[j]->piece_location->row = 1;
		}
	}

	newgame->blacks[0]->piece_type = BLACK_ROOK;
	newgame->blacks[1]->piece_type = BLACK_KNIGHT;
	newgame->blacks[2]->piece_type = BLACK_BISHOP;
	newgame->blacks[3]->piece_type = BLACK_QUEEN;
	newgame->blacks[4]->piece_type = BLACK_KING;
	newgame->blacks[5]->piece_type = BLACK_BISHOP;
	newgame->blacks[6]->piece_type = BLACK_KNIGHT;
	newgame->blacks[7]->piece_type = BLACK_ROOK;
	for (int i=8; i<16;i++){
		newgame->blacks[i]->piece_type = BLACK_PAWN;
	}
	for (int i = 0; i < 16; i++) {
		newgame->blacks[i]->alive = 1;
		newgame->blacks[i]->color = 0;
		newgame->blacks[i]->piece_location->column = (char)(i%8);
		if (newgame->blacks[i]->piece_type != BLACK_PAWN) {
			newgame->blacks[i]->piece_location->row = 7;
		} else {
			newgame->blacks[i]->piece_location->row = 6;
		}
	}

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

	copy->current_turn = cur_game->current_turn;
	copy->difficulty = cur_game->difficulty;
	copy->game_mode = cur_game->game_mode;
	copy->user_color = cur_game->user_color;

	// initialize new pieces

	for (int i=0; i<16; i++){
		copy->whites[i]->alive = cur_game->whites[i]->alive;
		copy->whites[i]->color = cur_game->whites[i]->color;
		copy->whites[i]->piece_location->row = cur_game->whites[i]->piece_location->row;
		copy->whites[i]->piece_location->column = cur_game->whites[i]->piece_location->column;
		copy->whites[i]->piece_type = cur_game->whites[i]->piece_type;

		copy->blacks[i]->alive = cur_game->blacks[i]->alive;
		copy->blacks[i]->color = cur_game->blacks[i]->color;
		copy->blacks[i]->piece_location->row = cur_game->blacks[i]->piece_location->row;
		copy->blacks[i]->piece_location->column = cur_game->blacks[i]->piece_location->column;
		copy->blacks[i]->piece_type = cur_game->blacks[i]->piece_type;
	}
	return copy;
}

void game_destroy (game* cur_game) {
	//array_list_destroy(cur_game->history);
	for (int i=15; i>=0; i--){
		destroy_piece(cur_game->blacks[i]);
	}
	//free(cur_game->blacks);

	for (int i=15; i>=0; i--){
		destroy_piece(cur_game->whites[i]);
	}
	free(cur_game->whites);
	free(cur_game->blacks);
	free(cur_game);
}

void print_board(game* cur_game){

	if (cur_game == NULL)
		return ;

	for (int i=8; i>=1; i--){
		printf("%d| ", i);
		for (int j=0; j<8 ; j++){
			printf("%c ", cur_game->board[i-1][j]);
		}
		printf("|\n");
	}
	printf("  -----------------\n   ");
	for (char c = 'A'; c <= 'G'; c++){
		printf("%c ", c);
	}
	printf("H");
	printf("\n");
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

// check if enemy threaten the king in diagonals - used for bishop and queen
bool check_diagonals(game* cur_game, const location* king_loc, location* enemy_loc){
	// up right diagonal
	for (int i=1; i<8; i++){

		if ((enemy_loc->row + i == king_loc->row) && (enemy_loc->column + i == king_loc->column)){
			return true;
		}

		if (enemy_loc->row + i > 7 || enemy_loc->column + i > 7){
			break;
		}

		if (cur_game->board[enemy_loc->row + i][enemy_loc->column + i] != EMPTY_ENTRY){
			break;
		}
	}

	// up left diagonal
	for (int i=1; i<8; i++){
		if (enemy_loc->row - i == king_loc->row && enemy_loc->column+ i == king_loc->column){
			return true;
		}
		if (enemy_loc->row - i < 0 || enemy_loc->column + i > 7){
			break;
		}
		if (cur_game->board[enemy_loc->row - i][enemy_loc->column + i] != EMPTY_ENTRY){
			break;
		}
	}

	// down left diagonal
	for (int i=1; i<8; i++){
		if (enemy_loc->row - i == king_loc->row && enemy_loc->column - i == king_loc->column){
			return true;
		}
		if (enemy_loc->row - i < 0 || enemy_loc->column - i < 0){
			break;
		}
		if (cur_game->board[enemy_loc->row - i][enemy_loc->column - i] != EMPTY_ENTRY){
			break;
		}
	}

	// down right diagonal
	for (int i=1; i<8; i++){
		if (enemy_loc->row + i == king_loc->row && enemy_loc->column - i == king_loc->column){
			return true;
		}
		if (enemy_loc->row + i > 7 || enemy_loc->column- i < 0){
			break;
		}
		if (cur_game->board[enemy_loc->row + i][enemy_loc->column - i] != EMPTY_ENTRY){
			break;
		}
	}
	return false;
}

// check if enemy threaten the king in parallel - used for rook and queen
bool check_parallels(game* cur_game, const location* king_loc, location* enemy_loc){
	// up
	for (char i=1; i<8; i++){
		if (enemy_loc->column + i == king_loc->column && enemy_loc->row  == king_loc->row){
			return true;
		}

		if (enemy_loc->column + i < 7){
			break;
		}


		if (enemy_loc->column + i > 7 || cur_game->board[enemy_loc->row][enemy_loc->column + i] != EMPTY_ENTRY){
			break;
		}
	}

	// down
	for (char i=1; i<8; i++){
		if (enemy_loc->column - i == king_loc->column&& enemy_loc->row  == king_loc->row){
			return true;
		}

		if (enemy_loc->column - i < 0){
			break;
		}


		if (enemy_loc->column - i < 0 || cur_game->board[enemy_loc->row][enemy_loc->column - i] != EMPTY_ENTRY){
			break;
		}
	}

	// right
	for (int i=1; i<8; i++){
		if (enemy_loc->row + i == king_loc->row && enemy_loc->column == king_loc->column){
			return true;
		}

		if (enemy_loc->row + i > 7){
			break;
		}

		if (enemy_loc->row + i > 7 || cur_game->board[enemy_loc->row + i][enemy_loc->column] != EMPTY_ENTRY){
			break;
		}
	}

	// left
	for (int i=1; i<8; i++){
		if (enemy_loc->row - i == king_loc->row && enemy_loc->column == king_loc->column){
			return true;
		}

		if (enemy_loc->row - i < 0){
			break;
		}

		if (enemy_loc->row- i < 1 || cur_game->board[enemy_loc->row - i][enemy_loc->column] != EMPTY_ENTRY){
			break;
		}
	}
	return false;
}

void announce_check_user(int color) {
	if (color == 1) {
		printf("Check: white King is threatened!\n");
	} else {
		printf("Check: black King is threatened!\n");
	}
}

void announce_check_pc() {
	printf("Check!\n");
}

// if it's white's turn, white king cannot be threatened by a black piece, the opposite if it's black's turn
bool is_check(game* cur_game){
	if (cur_game == NULL){
		return false;
	}
	location* king_loc;
	piece** enemies;

	int color = (cur_game->current_turn + cur_game->user_color) %2;

	// white turn
	if (color == 1){
		king_loc = cur_game->whites[4]->piece_location;
		enemies = cur_game->blacks;
	}
	// black turn
	else{
		king_loc = cur_game->blacks[4]->piece_location;
		enemies = cur_game->whites;
	}

	for (int i=0; i<16; i++){

		// putting location into variable for readability
		location* enemy_loc = enemies[i]->piece_location;
		char enemy_type = enemies[i]->piece_type;
		if (enemies[i]->alive == 0){
			continue;
		}

		// black pawn
		if (enemy_type == BLACK_PAWN){
			if ((enemy_loc->row == (king_loc->row) + 1) &&
					((enemy_loc->column == (king_loc->column) + 1) ||(enemy_loc->column == (king_loc->column) - 1))){
				return true;
			}
		}

		// white pawn
		if (enemy_type == WHITE_PAWN){
			if ((enemy_loc->row == (king_loc->row) - 1) &&
					((enemy_loc->column == (king_loc->column) + 1) ||(enemy_loc->column == (king_loc->column) - 1))){
				return true;
			}
		}

		// knight
		if (enemy_type == BLACK_KNIGHT || enemy_type == WHITE_KNIGHT){
			if (((enemy_loc->column == (king_loc->column) + 2) && ((enemy_loc->row == (king_loc->row) + 1) ||(enemy_loc->row == (king_loc->row) - 1))) ||
				((enemy_loc->column == (king_loc->column) - 2) && ((enemy_loc->row == (king_loc->row) + 1) ||(enemy_loc->row == (king_loc->row) - 1)))||
				((enemy_loc->row == (king_loc->row) + 2) && ((enemy_loc->column == (king_loc->column) + 1) ||(enemy_loc->column == (king_loc->column) - 1)))||
				((enemy_loc->row == (king_loc->row) - 2) && ((enemy_loc->column == (king_loc->column) + 1) ||(enemy_loc->column == (king_loc->column) - 1)))){
				return true;
			}
		}

		// bishop
		if (enemy_type == BLACK_BISHOP || enemy_type == WHITE_BISHOP){
			if (check_diagonals(cur_game, king_loc, enemy_loc) == true){
				return true;
			}
		}

		// rook
		if (enemy_type == BLACK_ROOK || enemy_type == WHITE_ROOK){
			if (check_parallels(cur_game, king_loc, enemy_loc) == true){
				return true;
			}
		}

		// queen
		if (enemy_type == BLACK_QUEEN || enemy_type == WHITE_QUEEN){
			if ((check_parallels(cur_game, king_loc, enemy_loc) == true) ||
				(check_diagonals(cur_game, king_loc, enemy_loc) == true)){
				return true;
			}
		}

		// king
		if (enemy_type == BLACK_KING || enemy_type == WHITE_KING){
			if (((king_loc->row - (enemy_loc->row)) <= 1 && (king_loc->row - (enemy_loc->row)) >= -1) &&
				((king_loc->column - (enemy_loc->column)) <= 1 && (king_loc->column - (enemy_loc->column)) >= -1)){
				return true;
			}
		}
	}
	return false;
}
