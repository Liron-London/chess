/*
 * setting.h
 *
 *  Created on: Aug 5, 2017
 *      Author: Gal
 */

#ifndef SETTING_H_
#define SETTING_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "game.h"

typedef enum {
    GAME_MODE,
    DIFFICULTY,
    USER_COLOR,
    LOAD,
    DEFAULT_GAME,
    PRINT_SETTINGS,
    QUIT,
    START
} command_type;

typedef struct command_t {
	command_type cmd;
    bool validArg; //is set to true if the line contains a valid argument
    int arg;
} Command;

bool parse_is_int(const char* str);

/*
 * get command and change game if needed
 */
Command parse_line(game* cur_game, const char* str);

/*
 * creates a defualt game updates it according to user settings (with while loop)
 */
int set_game();

#endif /* SETTING_H_ */
