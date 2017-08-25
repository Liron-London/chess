/*
 * game.c
 *
 *  Created on: Aug 6, 2017
 *      Author: Gal
 */

#include "game.h"

/*
 * TODO
 * (1) need to change the size of the valid_moves array to 29 and initialize it to default locations (will make all checks much easier)
 * (2) in Is_valid_move there might be a memory leak in valid_locs (initialized as location* but needed to be location[64]
 */

piece* location_to_piece(game* game, location* loc){
	// printf("DEBUG: in location_to_piece\n");
	printf("DEBUG: location is: ROW %d, COL %d\n", loc->row, loc->column);
	char type = game->board[loc->row][loc->column];
	printf("DEBUG: type is %c\n", type);
	if (type == EMPTY_ENTRY){
		return NULL;
	}

	if (type > 'a'){
		for (int i=0; i<16;i++){
			printf("DEBUG: piece location is: ROW %d, COL %d\n", game->whites[i]->piece_location->row, game->whites[i]->piece_location->column);
			if (game->whites[i]->piece_location->row == loc->row && game->whites[i]->piece_location->column == loc->column){
				printf("DEBUG: NON-NULL is returned\n");
				return game->whites[i];
			}
		}
	}

	else{
		for (int i=0; i<16;i++){
			if (game->blacks[i]->piece_location->row == loc->row && game->blacks[i]->piece_location->column == loc->column){
				printf("DEBUG: NON-NULL is returned\n");
				return game->blacks[i];
			}
		}
	}
	printf("DEBUG: NULL is returned\n");
	return NULL;
}

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
	piece->piece_location->column = -1;
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

	newgame->whites = (piece**)malloc(16 * sizeof(piece));
	newgame->blacks = (piece**)malloc(16 * sizeof(piece));

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
	newgame->whites[5]->piece_type = WHITE_KNIGHT;
	newgame->whites[6]->piece_type = WHITE_BISHOP;
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
	newgame->blacks[5]->piece_type = BLACK_KNIGHT;
	newgame->blacks[6]->piece_type = BLACK_BISHOP;
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
	printf("DEBUG: board copy worked!\n");

	/* copying history
	for (int i=0; i<6; i++){
		copy->history[i] = cur_game->history[i];
	}
	*/

	copy->current_turn = cur_game->current_turn;
	copy->difficulty = cur_game->difficulty;
	copy->game_mode = cur_game->game_mode;
	copy->user_color = cur_game->user_color;
	for (int i=0; i<16; i++){
		copy->whites[i] = copy_piece(cur_game->whites[i]);
		copy->blacks[i] = copy_piece(cur_game->blacks[i]);
		printf("DEBUG: piece copy worked!\n");
	}
	printf("DEBUG: pieces copy worked!\n");
	return copy;
}

void game_destroy (game* cur_game) {
	//array_list_destroy(cur_game->history);
	for (int i=15; i>=0; i--){
		destroy_piece(cur_game->blacks[i]);
	}
	free(cur_game->blacks);

	for (int i=15; i>=0; i--){
		destroy_piece(cur_game->whites[i]);
	}
	free(cur_game->whites);
	free(cur_game);
}


void destroy_piece(piece* cur_piece){
	free(cur_piece->piece_location);
	free(cur_piece);
}

piece* copy_piece(piece* cur_piece){
	printf("DEBUG: in copy piece\n");
	piece* new_piece = create_piece();
	new_piece->alive = cur_piece->alive;
	new_piece->color = cur_piece->color;
	new_piece->piece_location->row = cur_piece->piece_location->row;
	printf("DEBUG: row copy worked\n");
	new_piece->piece_location->column = cur_piece->piece_location->column;
	printf("DEBUG: col copy worked\n");
	new_piece->piece_type = cur_piece->piece_type;
	printf("DEBUG: OUT!\n");
	return new_piece;
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


bool check_diagonals(game* cur_game, const location* king_loc, location* enemy_loc){
	// up right diagonal
	for (int i=0; i<8; i++){

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
	for (int i=0; i<8; i++){
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
	for (int i=0; i<8; i++){
		if (enemy_loc->row - i == king_loc->row && enemy_loc->column - i == king_loc->column){
			return true;
		}
		if (enemy_loc->row - i < 0 || enemy_loc->column- i < 0){
			break;
		}
		if (cur_game->board[enemy_loc->row - i][enemy_loc->column - i] != EMPTY_ENTRY){
			break;
		}
	}

	// down right diagonal
	for (int i=0; i<8; i++){
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

bool check_parallels(game* cur_game, const location* king_loc, location* enemy_loc){
	// up
	for (char i=0; i<8; i++){
		if (enemy_loc->column+ i > 7 || cur_game->board[enemy_loc->row][enemy_loc->column + i] != EMPTY_ENTRY){
			break;
		}
		if (enemy_loc->column+ i == king_loc->column && enemy_loc->row  == king_loc->row){
			return true;
		}
	}

	// down
	for (char i=0; i<8; i++){
		if (enemy_loc->column- i < 0 || cur_game->board[enemy_loc->row][enemy_loc->column - i] != EMPTY_ENTRY){
			break;
		}
		if (enemy_loc->column- i == king_loc->column&& enemy_loc->row  == king_loc->row){
			return true;
		}
	}

	// right
	for (int i=0; i<8; i++){
		if (enemy_loc->row + i > 7 || cur_game->board[enemy_loc->row + i][enemy_loc->column] != EMPTY_ENTRY){
			break;
		}
		if (enemy_loc->row + i == king_loc->row && enemy_loc->column == king_loc->column){
			return true;
		}
	}

	// left
	for (int i=0; i<8; i++){
		if (enemy_loc->row- i < 1 || cur_game->board[enemy_loc->row - i][enemy_loc->column] != EMPTY_ENTRY){
			break;
		}
		if (enemy_loc->row - i == king_loc->row && enemy_loc->column == king_loc->column){
			return true;
		}
	}
	return false;
}

// if it's white's turn, white king cannot be threatened by a black piece, the opposite if it's black's turn
bool is_check(game* cur_game){
	if (cur_game == NULL){
		return false;
	}
	location* king_loc;
	piece** enemies;

	// white turn
	if (cur_game->current_turn == 1){
		printf("KING IS WHITE\n");
		king_loc = cur_game->whites[4]->piece_location;
		enemies = cur_game->blacks;
	}
	// black turn
	else{
		printf("KING IS BLACK\n");
		king_loc = cur_game->blacks[4]->piece_location;
		printf("DEBUG: king loc is ROW %d, COL %d\n", king_loc->row, king_loc->column);
		enemies = cur_game->whites;
	}

	for (int i=0; i<16; i++){

		// putting location into variable for readability
		location* enemy_loc = enemies[i]->piece_location;
		printf("DEBUG: enemy loc is ROW %d, COL %d\n", enemy_loc->row, enemy_loc->column);
		char enemy_type = enemies[i]->piece_type;
		printf("DEBUG: enemy type %c\n",enemy_type);

		// black pawn
		if (enemy_type == BLACK_PAWN){
			if ((enemy_loc->column == (king_loc->column) + 1) &&
					((enemy_loc->row == (king_loc->row) + 1) ||(enemy_loc->row == (king_loc->row) - 1))){
				printf("FAILED BECAUSE OF A BLACK PAWN!\n");
				return true;
			}
		}

		// white pawn
		if (enemy_type == WHITE_PAWN){
			if ((enemy_loc->column == (king_loc->column) - 1) &&
					((enemy_loc->row == (king_loc->row) + 1) ||(enemy_loc->row == (king_loc->row) - 1))){
				printf("FAILED BECAUSE OF A WHITE PAWN!\n");
				return true;
			}
		}

		// knight
		if (enemy_type == BLACK_KNIGHT || enemy_type == WHITE_KNIGHT){
			if (((enemy_loc->column == (king_loc->column) + 2) && ((enemy_loc->row == (king_loc->row) + 1) ||(enemy_loc->row == (king_loc->row) - 1))) ||
				((enemy_loc->column == (king_loc->column) - 2) && ((enemy_loc->row == (king_loc->row) + 1) ||(enemy_loc->row == (king_loc->row) - 1)))||
				((enemy_loc->row == (king_loc->row) + 2) && ((enemy_loc->column == (king_loc->column) + 1) ||(enemy_loc->column == (king_loc->column) - 1)))||
				((enemy_loc->row == (king_loc->row) - 2) && ((enemy_loc->column == (king_loc->column) + 1) ||(enemy_loc->column == (king_loc->column) - 1)))){
				printf("FAILED BECAUSE OF A KNIGHT!\n");
				printf("KING LOC IS: ROW: %d COL %c\n", king_loc->row, king_loc->column);
				printf("KNIGHT LOC IS: ROW: %d COL %c\n", enemy_loc->row, enemy_loc->column);
				return true;
			}
		}

		// bishop
		if (enemy_type == BLACK_BISHOP || enemy_type == WHITE_BISHOP){
			if (check_diagonals(cur_game, king_loc, enemy_loc) == true){
				printf("FAILED BECAUSE OF A BISHOP!\n");
				return true;
			}
		}

		// rook
		if (enemy_type == BLACK_ROOK || enemy_type == WHITE_ROOK){
			if (check_parallels(cur_game, king_loc, enemy_loc) == true){
				printf("FAILED BECAUSE OF A ROOK!\n");
				return true;
			}
		}

		// queen
		if (enemy_type == BLACK_QUEEN || enemy_type == WHITE_QUEEN){
			if ((check_parallels(cur_game, king_loc, enemy_loc) == true) ||
				(check_diagonals(cur_game, king_loc, enemy_loc) == true)){
				printf("FAILED BECAUSE OF A QUEEN!\n");
				return true;
			}
		}

		// king
		if (enemy_type == BLACK_KING || enemy_type == WHITE_KING){
			if (((king_loc->row - (enemy_loc->row)) <= 1 && (king_loc->row - (enemy_loc->row)) >= -1) &&
				((king_loc->column - (enemy_loc->column)) <= 1 && (king_loc->column - (enemy_loc->column)) >= -1)){
				printf("FAILED BECAUSE OF A KING!\n");
				return true;
			}
		}
	}
	printf("DEBUG: check finished correctly\n");
	return false;
}
