#ifndef MINIMAX_H_INCLUDED
#define MINIMAX_H_INCLUDED

#include "game.h"
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

#endif // MINIMAX_H_INCLUDED
