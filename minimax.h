#ifndef MINIMAX_H_INCLUDED
#define MINIMAX_H_INCLUDED

#include "game.h"
#include "moves.h"
#include <limits.h>

/*
 * runs MiniMax and call set move
 */
int computer_move(game* game);

int get_score(game* game);

/*
 * Computes a board's score, returns 0 if game is NULL
 */
int scoring_function(game* game);

move* get_recommended_move_for_comp(game* game, int depth);

int alphabeta(game* node, int depth, int alpha, int beta, bool maximizing_player, move* best_move);

void all_valid_moves(game* game, move** all_valid_moves, int* amout_of_valid_moves);

#endif // MINIMAX_H_INCLUDED
