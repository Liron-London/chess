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
#include "file_handler.h"

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
 * creates a new command, returns the pointer to it
 */
Command* create_command();

/*
 * destroys a command using free
 */
void destroy_command(Command* command);

/*
 *  prompts the user to enter settings
 *  calls parse_line
 */
char* ask_for_settings(char* command_text);

/*
 * says if a string is number or not
 */
bool parse_is_int(const char* str);

/*
 * get command-string from user and checks validity of command
 * @params - current game, command object, return variable for load command
 * @return command*
 */
Command* parse_line(game* game, const char* str, Command* command, char* filename);

/*
 * prints the current game settings
 */
void print_settings(game* cur_game);

/*
 * prints an error message if the user typed in a level outside of 1-4
 */
void print_invalid_difficulty();

/*
 * creates a default game updates it according to user settings (with while loop)
 * returns 0 if the command exits the settings mode (start, quit, load)
 */
int set_game();

#endif /* SETTING_H_ */
