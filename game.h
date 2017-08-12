#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <stdio.h>
#include "array_list.h"
#include <stdbool.h>

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
#define EMPTY_ENTRY ' '

typedef struct location_t {
    int row;
    char column;
} location;

typedef struct piece_t {
    location* piece_location;
    char piece_type;
    int color;
} piece;

typedef struct game_t {
    int game_mode; // 1 = one player mode, 2 = two player mode
    int difficulty; // between 1-4
    int user_color; // 0 - black, 1 - white
    //array_list history; // for undo move
    int current_turn; //0 - PC or player 2, 1 - player one
    char board[8][8];
    piece whites[16];
    piece blacks[16];
} game;


/*
* checks that the King's not threatened
*/
bool is_check(game* cur_game, const piece* king, const piece* enemy_locs);


/*
 * checks if a piece threats the kings from diagonal
 */
bool check_diagonals(game* cur_game, location* king_loc, location* enemy_loc);

/*
 * checks if a piece threats the king from up/down/right/left
 */
bool check_parallels(game* cur_game, location* king_loc, location* enemy_loc);

/*
* returns a list of all valid moves, needs to call is_check to verify the King's not threatened
*/
location* valid_moves(game* cur_game, piece* cur_piece);

/*
* creates a new the game object (including allocating memory resources)
*/
game* game_create();

/*
* creates a copy of the game object
*/
game* game_copy(game* cur_game);
#endif // GAME_H_INCLUDED

/*
* destroys the game and frees all game-related memory resources
*/
void game_destroy (game* cur_game);

/*
* updates the game's board after a valid move
*/
// void set_move(game* cur_game, piece* cur_piece, location* dst_location);

/*
* prints the current board (in console mode)
*/
void print_board(game* cur_game);
