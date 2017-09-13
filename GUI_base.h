/*
 * GUI_base.h
 *
 *  Created on: Sep 12, 2017
 *      Author: liron
 */

#ifndef GUI_BASE_H_
#define GUI_BASE_H_
#include "SDL2/SDL.h"
#include "game.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)

/*
 * receives a rect object, checks if the mouse click was in it
 */
bool check_mouse_button_event(SDL_Event event, SDL_Rect rect);

#endif /* GUI_BASE_H_ */
