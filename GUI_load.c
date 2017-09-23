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
SDL_Rect load_button, back_button;
SDL_Surface* load_surfaces[5];
SDL_Texture* load_textures[5];

void free_load_resources() {
	for(int i = 0; i < 5; i++) {
		SDL_DestroyTexture(load_textures[i]);
	}
}

screen display_load_buttons(SDL_Window* window, SDL_Renderer* renderer, int selected) {
	int num_games = get_num_games();
	SDL_Log("num games is %d", num_games);
	int y = 15;
	char image_name[39];
	for (int i = 0; i < num_games; i++) {
		if (i != selected) {
			strcpy(image_name, "./images/game buttons/button-game");
		} else {
			strcpy(image_name, "./images/game buttons/selected-game");
		}
		char idx[2] = {i + 1 + '0', '\0'};
		strcat(image_name, idx);
		strcat(image_name, ".bmp");
		//		SDL_Log("image name is: %s", image_name);
		SDL_Surface* surface = SDL_LoadBMP(image_name);
		verify_surface(window, renderer, surface, LOAD_SCREEN);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		verify_texture(window, renderer, surface, texture, LOAD_SCREEN);

		SDL_QueryTexture(texture, NULL, NULL, &load_buttons[i].w, &load_buttons[i].h);
		load_buttons[i].w *= 0.6;
		load_buttons[i].h *= 0.6;
		load_buttons[i].x = (SCREEN_WIDTH - load_buttons[i].w) / 2;
		load_buttons[i].y = y;
		y += load_buttons[i].h + 15;

		SDL_RenderCopy(renderer, texture, NULL, &load_buttons[i]);
	}

	//adding a LOAD button - disabled if no game was selected
	char load_image_name[50];
	if (selected < 0) {
		strcpy(load_image_name, "./images/game buttons/disabled-load-button.bmp");
	} else {
		strcpy(load_image_name, "./images/game buttons/button-load-game.bmp");
	}
	SDL_Surface* load_surface = SDL_LoadBMP(load_image_name);
	verify_surface(window, renderer, load_surface, LOAD_SCREEN);
	SDL_Texture* load_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
	verify_texture(window, renderer, load_surface, load_texture, LOAD_SCREEN);

	SDL_QueryTexture(load_texture, NULL, NULL, &load_button.w, &load_button.h);
	load_button.w *= 0.6;
	load_button.h *= 0.6;
	load_button.x = (SCREEN_WIDTH - load_button.w) / 4;
	load_button.y = SCREEN_HEIGHT - load_button.h - 15;
	SDL_RenderCopy(renderer, load_texture, NULL, &load_button);

	//adding a BACK button
	SDL_Surface* back_surface = SDL_LoadBMP("./images/game buttons/back-button.bmp");
	verify_surface(window, renderer, back_surface, LOAD_SCREEN);
	SDL_Texture* back_texture = SDL_CreateTextureFromSurface(renderer, back_surface);
	verify_texture(window, renderer, back_surface, back_texture, LOAD_SCREEN);

	SDL_QueryTexture(back_texture, NULL, NULL, &back_button.w, &back_button.h);
	back_button.w *= 0.6;
	back_button.h *= 0.6;
	back_button.x = (SCREEN_WIDTH - back_button.w) * 0.75;
	back_button.y = SCREEN_HEIGHT - back_button.h - 15;
	SDL_RenderCopy(renderer, back_texture, NULL, &back_button);

	return LOAD_SCREEN;
}

screen render_loading_screen(SDL_Window* window, SDL_Renderer* renderer, int selected) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
	SDL_RenderClear(renderer);
	screen display_screen;
	display_screen = display_load_buttons(window, renderer, selected);
	SDL_RenderPresent(renderer);
	return display_screen;
}

screen loading_screen(SDL_Window* window, SDL_Renderer* renderer, screen prev_screen, game* game) {
	char filename[14];
	int num_games = get_num_games();
	screen display_screen = LOAD_SCREEN;
	int selected_game = -1;

	render_loading_screen(window, renderer, -1);

	bool loading_screen = true;
	SDL_Event event;
	while (loading_screen) {
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				loading_screen = false;
				return EXIT;
			case SDL_MOUSEBUTTONUP:
				for (int i = 0; i < num_games; i++) {
					if (check_mouse_button_event(event, load_buttons[i])) {
						render_loading_screen(window, renderer, i);
						selected_game = i;
					}
				}
				if (check_mouse_button_event(event, back_button)) {
					display_screen = prev_screen;
					loading_screen = false;
				} else if (check_mouse_button_event(event, load_button) && selected_game >= 0) {
					generate_filename(selected_game + 1, filename);
					//					SDL_Log("filename is: %s", filename);
					display_screen = GAME_SCREEN;
					loading_screen = false;
					load_game(game, filename);
					SDL_Log("loading screen is false");
				}
			}
		}
	}
	free_load_resources();
	return display_screen;
}

