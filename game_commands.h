/*
 * game_commands.h
 *
 *  Created on: Aug 5, 2017
 *      Author: Gal
 */

#ifndef GAME_COMMANDS_H_
#define GAME_COMMANDS_H_

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "moves.h"
#include "minimax.h"

typedef enum {
    MOVE,
    SAVE,
    UNDO,
    RESET,
    GAME_QUIT,
    ILLIGAL_COMMAND
} game_command_type;

typedef struct game_command_t {
	game_command_type cmd;
    bool validArg; //is set to true if the line contains a valid argument
    move* move;
} Gamecommand;

/*
 * prints the "XXX player - enter your move" message according to the current turn
 */
void ask_for_move(game* cur_game);

/*
 * for move - check if the command is valid and call set_move
 */
Gamecommand* game_command_parse_line(char* str, char* file_name);

Gamecommand* game_command_create();

void game_command_destroy(Gamecommand* command);
/*
 * called right after user entered the command "START" and manages the game
 */
int game_play(game* game);

void announce_invalid_location();

void announce_computer_move(game* game, move* move);

#endif /* GAME_COMMANDS_H_ */
