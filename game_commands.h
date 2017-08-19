/*
 * game_commands.h
 *
 *  Created on: Aug 5, 2017
 *      Author: Gal
 */

#ifndef GAME_COMMANDS_H_
#define GAME_COMMANDS_H_

#include "game.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum {
    MOVE,
    SAVE,
    UNDO,
    RESET,
    GAME_QUIT
} game_command_type;

typedef struct game_command_t {
	game_command_type cmd;
    bool validArg; //is set to true if the line contains a valid argument
    move* move;
} Gamecommand;

/*
 * for move - check if the command is valid and call set_move
 */
Gamecommand game_command_parse_line(const char* str);

/*
 * called right after user entered the command "START" and manges the game
 */
int game_play(game* game);



#endif /* GAME_COMMANDS_H_ */
