#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <stdio.h>
#include "array_list.h"


typedef struct game_t {
    int game_mode; // 1 = one player mode, 2 = two player mode
    int difficulty; // between 1-4
    int user_color; // 0 - black, 1 - white
    array_list history; // for undo move
} GAME;


#endif // GAME_H_INCLUDED
