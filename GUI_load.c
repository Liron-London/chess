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

screen display_load_buttons(SDL_Window* window, SDL_Renderer* renderer, game* game, screen prev_screen) {
	int num_games = get_num_games();
	int y = 15;
	for (int i = 0; i < num_games; i++) {
		char image_name[39] = "./images/game buttons/button-game";
		strcat(image_name, (char)(i));
		strcat(image_name, ".bmp");

		SDL_Surface* surface = SDL_LoadBMP(image_name);
		verify_surface(window, renderer, surface, LOAD_SCREEN);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		verify_texture(window, renderer, texture, LOAD_SCREEN);
		SDL_FreeSurface(surface);

		SDL_QueryTexture(texture, NULL, NULL, &load_buttons[i].w, &load_buttons[i].h);
		save_game_rec.x = (SCREEN_WIDTH - save_game_rec.w) / 2;
		save_game_rec.y = y;
		y += load_buttons[i].h + 15;
	}

	return prev_screen;
}

