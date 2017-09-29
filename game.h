#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//Definitions
#define WHITE_PAWN 'm'
#define BLACK_PAWN 'M'
#define WHITE_BISHOP 'b'
#define BLACK_BISHOP 'B'
#define WHITE_ROOK 'r'
#define BLACK_ROOK 'R'
#define WHITE_KNIGHT 'n'
#define BLACK_KNIGHT 'N'
#define WHITE_QUEEN 'q'
#define BLACK_QUEEN 'Q'
#define WHITE_KING 'k'
#define BLACK_KING 'K'
#define EMPTY_ENTRY '_'

typedef struct location_t {
    int row;
    int column;
} location;

typedef struct piece_t {
    location* piece_location;
    char piece_type;
    int color;
    int alive; //0 - piece was captured, 1 - piece is alive
} piece;

typedef struct game_t {
    int game_mode; // 1 = one player mode, 2 = two player mode
    int difficulty; // between 1-4
    int user_color; // 0 - black, 1 - white
    int current_turn; //0 - PC or player 2, 1 - player one
    char board[8][8];
    piece** whites;
    piece** blacks;
} game;

typedef struct move_t {
	location* source;
	location* dest;
} move;

/*
 * returns the player-color of the player of the current turn, based on current_turn and user_color
 */
int current_turn_color(game* game);

piece* location_to_piece(game* game, location* loc);

piece* copy_piece(piece* cur_piece);

void destroy_piece(piece* cur_piece);

/*
 * create an "empty" piece
 */
piece* create_piece();

/*
 * called when the user causes a check state
 * prints which king is threatened
 */
void announce_check_user(int color);

/*
 * called when the computer causes a check state
 * prints "Check!"
 */
void announce_check_pc();

/*
* checks that the King's not threatened
*/
bool is_check(game* cur_game);

/*
 * checks if a piece threats the kings from diagonal
 */
bool check_diagonals(game* cur_game, const location* king_loc, location* enemy_loc);

/*
 * checks if a piece threats the king from up/down/right/left
 */
bool check_parallels(game* cur_game, const location* king_loc, location* enemy_loc);


/*
* creates a new the game object (including allocating memory resources)
*/
game* game_create();

/*
* creates a copy of the game object
*/
game* game_copy(game* cur_game);

/*
* destroys the game and frees all game-related memory resources
*/
void game_destroy (game* cur_game);

/*
* called by game_parse_line
* updates the game's board after a valid move
*/
void set_move(game* cur_game, move* cur_move);

/*
* prints the current board (in console mode)
*/
void print_board(game* cur_game);

void change_turn(game* cur_game);

location* create_location();

location* copy_location(location* loc);

void destroy_location(location* loc);

#endif // GAME_H_INCLUDED
