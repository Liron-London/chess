/*
 * game_commands.h
 *
 *  Created on: Aug 5, 2017
 *      Author: Gal
 */

#ifndef GAME_COMMANDS_H_
#define GAME_COMMANDS_H_

#include "game.h"

typedef enum {
    MOVE,
    SAVE,
    UNDO,
    RESET,
    QUIT
} game_command_type;

Command game_parse_line(const char* str);

/*
 * called right after user entered the command "START" and manges the game
 */
int game_play(game* game);



#endif /* GAME_COMMANDS_H_ */
