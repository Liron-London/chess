/*
 * GUI.h
 *
 *  Created on: Sep 11, 2017
 *      Author: liron
 */

#ifndef GUI_H_
#define GUI_H_
#include <stdbool.h>
#include <SDL.h>
//#include "GUI_base.h"
//#include "GUI_load.h"
//#include "GUI_display_game.h"


int gui();
bool check_mouse_button_event(SDL_Event event, SDL_Rect rect);

///*
// * presents the "select game difficulty" pop up
// * on "back" - returns to "select game mode"
// */
//screen set_difficulty_dialog(game* new_game)
//
///*
// * presents the "select game mode" pop up
// */
//screen set_game_mode_dialog(game* new_game);

#endif /* GUI_H_ */
