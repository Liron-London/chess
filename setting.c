/*
 * setting.c
 *
 *  Created on: Aug 8, 2017
 *      Author: Gal
 */

#include "setting.h"
#include "file_handler.h"
#include "debug.h"

Command* create_command() {
	Command* command = malloc(sizeof(Command));
	command->cmd = INVALID_COMMAND;
	command->arg = -1;
	command->validArg = false;
	return command;
}

void destroy_command(Command* command) {
	free(command);
}

bool parser_is_int(const char* str) {
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

void print_settings(game* cur_game){
	printf("SETTINGS:\n");
	printf("GAME_MODE: %i\n", cur_game->game_mode);
	if (cur_game->game_mode == 2) {
		printf("DIFFICULTY_LVL: %i\n", cur_game->difficulty);
		if (cur_game->user_color == 1){
			printf("USER_CLR: WHITE\n");
		}
		else{
			printf("USER_CLR: BLACK\n");
		}
	}
}

void print_invalid_difficulty() {
	printf("Wrong difficulty level. The value should be between 1 to 5\n");
}

void print_level_not_supported() {
	printf("Expert level not supported, please choose a value between 1 to 4:\n");
}

Command* parse_line(const char* str, Command* command, char* command_param) {

	char* str_copy = malloc(strlen(str) + 1);
	strcpy(str_copy, str);
	char* command_text = strtok(str_copy, " \t\n");

	command->validArg = false;
	command->cmd = INVALID_COMMAND;
	// TODO
	// can the command get ints in case the command is start or quit?

	if (strcmp(command_text, "quit") == 0){
		command->cmd = QUIT;
		command->validArg = true;
	}

	if (strcmp(command_text, "start") == 0) {
		command->cmd = START;
		command->validArg = true;
	}

	if (strcmp(command_text, "print_setting") == 0) {
		command->cmd = PRINT_SETTINGS;
	}

	if (strcmp(command_text, "load") == 0) {
		command->cmd = LOAD;
		strcpy(command_param, strtok(NULL, " \t\n"));
	}

	if (strcmp(command_text, "user_color") == 0) {
		strcpy(command_param, strtok(NULL, " \t\n"));
		command->cmd = USER_COLOR;
		if (parser_is_int(command_param) == true){
			command->arg = atoi(command_param);
			if (command->arg == 1 || command->arg == 2){
				command->validArg = true;
			}
		}
	}

	if (strcmp(command_text, "game_mode") == 0) {
		command->cmd = GAME_MODE;
		strcpy(command_param, strtok(NULL, " \t\n"));
		if (parser_is_int(command_param) == true){
			command->arg = atoi(command_param); // 1 for single player and 2 for two players
			if (command->arg == 1 || command->arg == 2){
				command->validArg = true;
			}
		}
	}

	if (strcmp(command_text, "difficulty") == 0) {
		strcpy(command_param, strtok(NULL, " \t\n"));
		command->cmd = DIFFICULTY;
		// TODO - in case we do the bonus we need to change the upper bound
		if (parser_is_int(command_param) == true) {
			command->arg = atoi(command_param);
			if (command->arg >= 1 && command->arg <= 4) {
				command->validArg = true;
			}
			else if (command->arg == 5) {
				print_level_not_supported();
			}
			else {
				print_invalid_difficulty();
			}
		}
	}

	if (strcmp(command_text, "default") == 0) {
		command->cmd = DEFAULT_GAME;
		command->validArg = true;

	}
	free(str_copy);
	return command;
}

char* ask_for_settings(char* command_text) {
	printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
	scanf(" %1024[^\n]", command_text);
	DEBUG("command text is: %s\n", command_text);
	return command_text;
}

int set_game() {
	game* new_game = game_create();
	Command* command = create_command();
	while(true) {

		char* command_text = malloc(1024 * sizeof(char));
		ask_for_settings(command_text);
		char command_param[100];
		parse_line(command_text, command, command_param);

		if (command->cmd == START) {
			if (new_game->game_mode == 2){
				new_game->user_color = 1;
			}
			if (new_game->game_mode == 1 && new_game->user_color == 0) {
				new_game->current_turn = 0;
			}
			free(command_text);
			destroy_command(command);
			game_play(new_game);
			return 0;
		}
		if (command->cmd == QUIT) {
			free(command_text);
			destroy_command(command);
			game_destroy(new_game);
			return 0;
		}
		if (command->cmd == GAME_MODE) {
			new_game->game_mode = command->arg;
			if (new_game->game_mode == 2) {
				new_game->user_color = 1;
				printf("Game mode is set to 2 players\n");
			} else {
				printf("Game mode is set to 1 player\n");
			}
		}
		if (command->cmd == DIFFICULTY) {
			new_game->difficulty = command->arg;

		}
		if (command->cmd == USER_COLOR) {
			new_game->user_color = command->arg;
		}
		if (command->cmd == LOAD) {
			load_game(new_game, command_param);
		}
		if (command->cmd == DEFAULT_GAME) {
			new_game->user_color = 1;
			new_game->game_mode = 1;
			new_game->difficulty = 2;
		}
		if (command->cmd == PRINT_SETTINGS) {
			print_settings(new_game);
		}
		if (command->cmd == INVALID_COMMAND) {

		}
		free(command_text);
	}
		return 1;
}
