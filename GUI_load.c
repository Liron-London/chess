/*
 * GUI_load.c
 *
 *  Created on: Sep 20, 2017
 *      Author: liron
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#include <SDL2/SDL.h>
#include "array_list.h"
#include "GUI_base.h"
#include "GUI_display_game.h"
#include "file_handler.h"

SDL_Rect load_buttons[5];
SDL_Surface* load_surfaces[5];
SDL_Texture* load_textures[5];

screen display_load_buttons(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
	SDL_RenderClear(renderer);

	int num_games = get_num_games();
	SDL_Log("num games is %d", num_games);
	int y = 15;
	for (int i = 0; i < num_games; i++) {
		char image_name[39] = "./images/game buttons/button-game";
		char idx[2] = {i + 1 + '0', '\0'};
		strcat(image_name, idx);
		strcat(image_name, ".bmp");
		SDL_Log("image name is: %s", image_name);
		SDL_Surface* surface = SDL_LoadBMP(image_name);
		verify_surface(window, renderer, surface, LOAD_SCREEN);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		verify_texture(window, renderer, surface, texture, LOAD_SCREEN);
		SDL_FreeSurface(surface);

		SDL_QueryTexture(texture, NULL, NULL, &load_buttons[i].w, &load_buttons[i].h);
		load_buttons[i].w /= 0.8;
		load_buttons[i].h /= 0.8;
		load_buttons[i].x = (SCREEN_WIDTH - load_buttons[i].w) / 2;
		load_buttons[i].y = y;
		y += load_buttons[i].h + 15;

		SDL_RenderCopy(renderer, texture, NULL, &load_buttons[i]);
	}
	SDL_RenderPresent(renderer);
	return LOAD_SCREEN;
}

//screen loading_screen(SDL_Window* window, SDL_Renderer* renderer, screen prev_screen) {
//	bool loading_screen = true;
//	while (loading_screen) {
//
//	}
//}

