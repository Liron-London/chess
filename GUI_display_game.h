/*
 * GUI_display_game.h
 *
 *  Created on: Sep 12, 2017
 *      Author: liron
 */

#ifndef GUI_DISPLAY_GAME_H_
#define GUI_DISPLAY_GAME_H_

#include <SDL.h>

typedef struct gui_piece_t {
	SDL_Rect rect;
	SDL_Texture* texture;
} gui_piece;

/*
 * displays the game screen's buttons (save, load etc.)
 */
screen display_game_buttons(SDL_Window* window, SDL_Renderer* renderer, int history_size);
/*
 * creates the objects to display in the game pane of the screen
 */
screen display_game_board(SDL_Window* window, SDL_Renderer* renderer);

/*
 * calls the displayers and manages events
 */
screen game_screen(SDL_Window* window, SDL_Renderer* renderer, game* game);

#endif /* GUI_DISPLAY_GAME_H_ */
