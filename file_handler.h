#ifndef FILE_HANDLER_H_INCLUDED
#define FILE_HANDLER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "setting.h"

/*
* loads game from XML file
* returns 0 if OK, 1 if error
*/
int load_game(game* cur_game, char* filename);

/*
* saves game to XML file
* returns 0 if OK, 1 if error
*/
int save_game(game* cur_game, char* filename);

#endif // FILE_HANDLER_H_INCLUDED
