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
char* tag_finder(char* input_file_text, char* tag);

/*
* loads game from XML file
* returns 0 if OK, 1 if error
*/
int load_game(game* cur_game, char* filename);

/*
 * same as load_game, without starting the game
 */
int gui_load_game(game* cur_game, char* filename);

void update_pieces_for_load(game* cur_game);

int get_num_games();

void default_save(game* game, int game_index);

/*
 * @params: index of requested file, char* to put the name in
 * fills the filename array with the full name of the requested file
 */
void generate_filename(int index, char* filename);

#endif // FILE_HANDLER_H_INCLUDED
