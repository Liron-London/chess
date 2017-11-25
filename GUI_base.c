/*
 * GUI_base.c
 *
 *  Created on: Sep 13, 2017
 *      Author: liron
 */
#include "GUI_base.h"

/*
 * Given an event and a rectangle, returns true if the event occurred within the rectangle
 */
bool check_mouse_button_event(SDL_Event event, SDL_Rect rect) {
	bool in_button = false;
	if (event.button.button == SDL_BUTTON_LEFT &&
			event.motion.x >= rect.x &&
			event.motion.x <= rect.x + rect.w &&
			event.motion.y >= rect.y &&
			event.motion.y <= rect.y +rect.h) {
		in_button = true;
	}
	return in_button;
}

/*
 * frees the relevant resources if SDL_LoadSurface fails
 * @Return value: the screen that needs to be presented - EXIT if an error occurred, prev_Screen by default
 */
screen verify_surface(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, screen cur_screen) {
	if (!surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT;
	}
	return cur_screen;
}

/*
 * frees the surface that was used to create the texture
 * frees the relevant resources if SDL_LoadTexture fails
 * @Return value: the screen that needs to be presented - EXIT if an error occurred, prev_Screen by default
 */
screen verify_texture(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, screen cur_screen) {
	SDL_FreeSurface(surface);
	if (!texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT;
	}
	return cur_screen;
}
