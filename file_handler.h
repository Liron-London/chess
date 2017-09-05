#ifndef FILE_HANDLER_H_INCLUDED
#define FILE_HANDLER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "setting.h"

/*
* saves game to XML file
* returns 0 if OK, 1 if error
*/
int save_game(game* cur_game, char* filename);

/*
 * @params text from xml file, the tag to search for, return-variable in which the relevant text
 * will be copied
 */
void tag_finder(char* input_file_text, char* tag, char* content);

/*
* loads game from XML file
* returns 0 if OK, 1 if error
*/
int load_game(game* cur_game, char* filename);

#endif // FILE_HANDLER_H_INCLUDED
