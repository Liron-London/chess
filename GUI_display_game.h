/*
 * GUI_display_game.h
 *
 *  Created on: Sep 12, 2017
 *      Author: liron
 */

#ifndef GUI_DISPLAY_GAME_H_
#define GUI_DISPLAY_GAME_H_

#include <SDL2/SDL.h>

screen display_game_buttons(SDL_Window* window, SDL_Renderer* renderer);

/*
 * calls the displayers and manages events
 */
screen game_screen(SDL_Window* window, SDL_Renderer* renderer, game* game);

#endif /* GUI_DISPLAY_GAME_H_ */
