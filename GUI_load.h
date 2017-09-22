/*
 * GUI_load.h
 *
 *  Created on: Sep 20, 2017
 *      Author: liron
 */

#ifndef GUI_LOAD_H_
#define GUI_LOAD_H_

/*
 * presents the possible LOAD buttons
 */
screen display_load_buttons(SDL_Window* window, SDL_Renderer* renderer);

/*
 * manages the LOAD GAME screen's events
 */
screen loading_screen(SDL_Window* window, SDL_Renderer* renderer, screen prev_screen, game* game);

#endif /* GUI_LOAD_H_ */
