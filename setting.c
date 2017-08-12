/*
 * setting.c
 *
 *  Created on: Aug 8, 2017
 *      Author: Gal
 */

#include "setting.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * says if a string is number or not
 */
bool parser_is_int(const char* str){
 char ch;
	if (*str == '-') {
		++str;
	}
	for (unsigned i = 0; i < strlen(str); i++) {
		ch = str[i];
		if (ch < 48 || ch > 57) {
			return false;
		}
	}
	return true;
}

Command parse_line(const char* str){
	char* str_copy = malloc(strlen(str) + 1);
	strcpy(str_copy, str);
	char* command_text = strtok(str_copy, " \t\n");
	printf("%s \n", command_text);
	char* command_int = strtok(NULL, " \t\n");
	printf("%s \n", command_int);

	Command command;
	command.validArg = false;
	command.cmd = INVALID_LINE;

	// TODO
	// can the command get ints in case the command is start or quit?

	if (strcmp(command_text, "quit") == 0){
		command.cmd = QUIT;
		command.validArg = true;
	}

	if (strcmp(command_text, "start") == 0) {
		command.cmd = START;
		command.validArg = true;
	}

	if (strcmp(command_text, "print setting") == 0) {
		command.cmd = PRINT_SETTINGS;
	}

	// argument is not int - need to think what we should do...
	if (strcmp(command_text, "load") == 0) {
		command.cmd = LOAD;
	}

	if (strcmp(command_text, "user_color") == 0) {
		command.cmd = USER_COLOR;
		if (parser_is_int(command_int) == true){
			command.arg = atoi(command_int);
			if (command_int == 1 || command_int == 2){
				command.validArg = true;
			}
		}
	}

	if (strcmp(command_text, "game_mode") == 0) {
		command.cmd = GAME_MODE;
		if (parser_is_int(command_int) == true){
			command.arg = command_int; // 1 for single player and 2 for two players
			if (command_int == 1 || command_int == 2){
				command.validArg = true;
			}
		}
	}

	if (strcmp(command_text, "difficulty") == 0) {
		command.cmd = DIFFICULTY;
		// TODO - in case we do the bonus we need to change the upper bound
		if (parser_is_int(command_int) == true){
			command.arg = atoi(command_int);
			if (command_int >= 1 && command_int <= 4){
				command.validArg = true;
			}
		}
	}

	if (strcmp(command_text, "default") == 0) {
		command.cmd = DEFAULT_GAME;
		command.validArg = true;
	}




}