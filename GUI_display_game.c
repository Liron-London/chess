/*
 * GUI_display_game.c
 *
 *  Created on: Sep 12, 2017
 *      Author: liron
 */
#include <stdbool.h>
#include <stdio.h>
//#include <SDL2/SDL.h>
#include "GUI_base.h"
#include "GUI_display_game.h"

int display_game_buttons(SDL_Renderer* renderer, SDL_Window* window) {
	//Load RESTART GAME button image as surface
	SDL_Surface* restart_game_surface = SDL_LoadBMP("./images/game buttons/button-restart.bmp");
	if (!restart_game_surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create RESTART GAME texture from surface
	SDL_Texture* restart_game_texture = SDL_CreateTextureFromSurface(renderer, restart_game_surface);
	if (!restart_game_texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_FreeSurface(restart_game_surface);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create rectangle
	SDL_Rect restart_game_rec = { .x = 0, .y = 30, .w = 600, .h = 600};

	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(restart_game_texture, NULL, NULL, &restart_game_rec.w, &restart_game_rec.h);
	restart_game_rec.x = SCREEN_WIDTH - restart_game_rec.w;
	restart_game_rec.y = (SCREEN_HEIGHT + restart_game_rec.h) + 30;
	restart_game_rec.w /= 4;
	restart_game_rec.h /= 4;

	//Load SAVE GAME button image as surface
	SDL_Surface* save_game_surface = SDL_LoadBMP("./images/game buttons/button-save.bmp");
	if (!save_game_surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create SAVE GAME texture from surface
	SDL_Texture* save_game_texture = SDL_CreateTextureFromSurface(renderer, save_game_surface);
	if (!save_game_texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_FreeSurface(save_game_surface);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create rectangle
	SDL_Rect save_game_rec = { .x = 0, .y = 30, .w = 600, .h = 600};

	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(save_game_texture, NULL, NULL, &save_game_rec.w, &save_game_rec.h);
	save_game_rec.x = SCREEN_WIDTH - save_game_rec.w;
	save_game_rec.y = (restart_game_rec.y + restart_game_rec.h) + 15;
	save_game_rec.w /= 4;
	save_game_rec.h /= 4;

	//Load LOAD GAME button image as surface
	SDL_Surface* load_game_surface = SDL_LoadBMP("./images/game buttons/button-load-game.bmp");
	if (!load_game_surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create SAVE GAME texture from surface
	SDL_Texture* load_game_texture = SDL_CreateTextureFromSurface(renderer, load_game_surface);
	if (!load_game_texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_FreeSurface(load_game_surface);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create rectangle
	SDL_Rect load_game_rec = { .x = 0, .y = 30, .w = 600, .h = 600};

	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(load_game_texture, NULL, NULL, &load_game_rec.w, &load_game_rec.h);
	load_game_rec.x = SCREEN_WIDTH - load_game_rec.w;
	load_game_rec.y = (save_game_rec.y + save_game_rec.h) + 15;
	load_game_rec.w /= 4;
	load_game_rec.h /= 4;

	//Load UNDO MOVE button image as surface
	SDL_Surface* undo_move_surface = SDL_LoadBMP("./images/game buttons/button-undo-move.bmp");
	if (!undo_move_surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create UNDO MOVE texture from surface
	SDL_Texture* undo_move_texture = SDL_CreateTextureFromSurface(renderer, undo_move_surface);
	if (!undo_move_texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_FreeSurface(undo_move_surface);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create rectangle
	SDL_Rect undo_move_rec = { .x = 0, .y = 30, .w = 600, .h = 600};

	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(undo_move_texture, NULL, NULL, &undo_move_rec.w, &undo_move_rec.h);
	undo_move_rec.x = SCREEN_WIDTH - undo_move_rec.w;
	undo_move_rec.y = (load_game_rec.y + load_game_rec.w) + 15;
	undo_move_rec.w /= 4;
	undo_move_rec.h /= 4;

	//Load MAIN MENU button image as surface
	SDL_Surface* main_menu_surface = SDL_LoadBMP("./images/game buttons/button-main-menu.bmp");
	if (!main_menu_surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create MAIN MENU texture from surface
	SDL_Texture* main_menu_texture = SDL_CreateTextureFromSurface(renderer, main_menu_surface);
	if (!main_menu_texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_FreeSurface(main_menu_surface);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create rectangle
	SDL_Rect main_menu_rec = { .x = 0, .y = 30, .w = 600, .h = 600};

	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(main_menu_texture, NULL, NULL, &main_menu_rec.w, &main_menu_rec.h);
	main_menu_rec.x = SCREEN_WIDTH - main_menu_rec.w;
	main_menu_rec.y = (undo_move_rec.y + undo_move_rec.h) + 15;
	main_menu_rec.w /= 4;
	main_menu_rec.h /= 4;

	//Load QUIT button image as surface
	SDL_Surface* quit_surface = SDL_LoadBMP("./images/game buttons/button-quit.bmp");
	if (!quit_surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create MAIN MENU texture from surface
	SDL_Texture* quit_texture = SDL_CreateTextureFromSurface(renderer, quit_surface);
	if (!quit_texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_FreeSurface(quit_surface);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create rectangle
	SDL_Rect quit_rec = { .x = 0, .y = 30, .w = 600, .h = 600};

	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(quit_texture, NULL, NULL, &quit_rec.w, &quit_rec.h);
	quit_rec.x = SCREEN_WIDTH - quit_rec.w;
	quit_rec.y = (main_menu_rec.y + main_menu_rec.h) + 15;
	quit_rec.w /= 4;
	quit_rec.h /= 4;

	return 0;
}

/*
int display_game_board(game* game, SDL_Renderer* renderer, SDL_Window* window) {
	return 0;
}
*/
