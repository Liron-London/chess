/*
 * game_commands.h
 *
 *  Created on: Aug 5, 2017
 *      Author: Gal
 */

#ifndef GAME_COMMANDS_H_
#define GAME_COMMANDS_H_

typedef enum {
    MOVE,
    SAVE,
    UNDO,
    RESET,
    QUIT
} game_command_type;

Command game_parse_line(const char* str);


#endif /* GAME_COMMANDS_H_ */
