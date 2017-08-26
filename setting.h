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
#include <string.h>
#include "game.h"
#include "game_commands.h"

typedef enum {
    GAME_MODE,
    DIFFICULTY,
    USER_COLOR,
    LOAD,
    DEFAULT_GAME,
    PRINT_SETTINGS,
    QUIT,
    START,
    INVALID_COMMAND
} command_type;

typedef struct command_t {
	command_type cmd;
    bool validArg; //is set to true if the line contains a valid argument
    int arg;
} Command;


/*
 *  prompts the user to enter settings
 *  calls parse_line
 */
void ask_for_settings();

/*
 * says if a string is number or not
 */
bool parse_is_int(const char* str);

/*
 * get command-string from user and checks validity of command
 */
Command* parse_line(game* game, const char* str, Command* command);

/*
 * prints the current game settings
 */
void print_settings(game* cur_game);

/*
 * creates a default game updates it according to user settings (with while loop)
 */
int set_game();

#endif /* SETTING_H_ */
