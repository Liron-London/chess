/*
 * GUI_base.h
 *
 *  Created on: Sep 12, 2017
 *      Author: liron
 */

#ifndef GUI_BASE_H_
#define GUI_BASE_H_
#include <SDL2.h>
#include "game.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)

typedef enum {
	EXIT,
	GAME_SCREEN,
	MENU_SCREEN,
	LOAD_SCREEN
} screen;

/*
 * receives a rect object, checks if the mouse click was in it
 */
bool check_mouse_button_event(SDL_Event event, SDL_Rect rect);

/*
 * verifies that the surface was created correctly
 * if not - frees resources and returns EXIT
 * else returns current screen
 */
screen verify_surface(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, screen cur_screen);

/*
 * verifies that the texture was created correctly
 * if not - frees resources and returns EXIT
 * else returns current screen
 */
screen verify_texture(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, screen cur_screen);
#endif /* GUI_BASE_H_ */
