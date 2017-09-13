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

SDL_Rect restart_game_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect save_game_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect load_game_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect undo_move_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect main_menu_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect quit_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect game_board_rec = { .x = 0, .y = 0, .w = 600, .h = 600};

//save_rec, load_game_rec, undo_move_rec, main_menu_rec, quit_rec;

screen display_game_buttons(SDL_Window* window, SDL_Renderer* renderer) {
	//Load RESTART GAME button image as surface
	SDL_Surface* restart_game_surface = SDL_LoadBMP("./images/game buttons/button-restart.bmp");
	if (!restart_game_surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT;
	}

	//Create RESTART GAME texture from surface
	SDL_Texture* restart_game_texture = SDL_CreateTextureFromSurface(renderer, restart_game_surface);
	if (!restart_game_texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_FreeSurface(restart_game_surface);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT;
	}

	//Create rectangle


	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(restart_game_texture, NULL, NULL, &restart_game_rec.w, &restart_game_rec.h);
	restart_game_rec.w /=3;
	restart_game_rec.h /=3;
	restart_game_rec.x = SCREEN_WIDTH - restart_game_rec.w;
	restart_game_rec.y = (restart_game_rec.h) + 30;

	//Load SAVE GAME button image as surface
	SDL_Surface* save_game_surface = SDL_LoadBMP("./images/game buttons/button-save.bmp");
	if (!save_game_surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT;
	}

	//Create SAVE GAME texture from surface
	SDL_Texture* save_game_texture = SDL_CreateTextureFromSurface(renderer, save_game_surface);
	if (!save_game_texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_FreeSurface(save_game_surface);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT;
	}

	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(save_game_texture, NULL, NULL, &save_game_rec.w, &save_game_rec.h);
	save_game_rec.w /=3;
	save_game_rec.h /=3;
	save_game_rec.x = SCREEN_WIDTH - save_game_rec.w;
	save_game_rec.y = (restart_game_rec.y + restart_game_rec.h) + 15;

	//Load LOAD GAME button image as surface
	SDL_Surface* load_game_surface = SDL_LoadBMP("./images/game buttons/button-load-game.bmp");
	if (!load_game_surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT;
	}

	//Create SAVE GAME texture from surface
	SDL_Texture* load_game_texture = SDL_CreateTextureFromSurface(renderer, load_game_surface);
	if (!load_game_texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_FreeSurface(load_game_surface);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT;
	}

	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(load_game_texture, NULL, NULL, &load_game_rec.w, &load_game_rec.h);
	load_game_rec.w /=3;
	load_game_rec.h /=3;
	load_game_rec.x = SCREEN_WIDTH - load_game_rec.w;
	load_game_rec.y = (save_game_rec.y + save_game_rec.h) + 15;

	//Load UNDO MOVE button image as surface
	SDL_Surface* undo_move_surface = SDL_LoadBMP("./images/game buttons/button-undo-move.bmp");
	if (!undo_move_surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT;
	}

	//Create UNDO MOVE texture from surface
	SDL_Texture* undo_move_texture = SDL_CreateTextureFromSurface(renderer, undo_move_surface);
	if (!undo_move_texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_FreeSurface(undo_move_surface);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT;
	}

	//Create rectangle

	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(undo_move_texture, NULL, NULL, &undo_move_rec.w, &undo_move_rec.h);
	undo_move_rec.w /=3;
	undo_move_rec.h /=3;
	undo_move_rec.x = SCREEN_WIDTH - undo_move_rec.w;
	undo_move_rec.y = (load_game_rec.y + load_game_rec.h) + 15;

	//Load MAIN MENU button image as surface
	SDL_Surface* main_menu_surface = SDL_LoadBMP("./images/game buttons/button-main-menu.bmp");
	if (!main_menu_surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT;
	}

	//Create MAIN MENU texture from surface
	SDL_Texture* main_menu_texture = SDL_CreateTextureFromSurface(renderer, main_menu_surface);
	if (!main_menu_texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_FreeSurface(main_menu_surface);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT;
	}

	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(main_menu_texture, NULL, NULL, &main_menu_rec.w, &main_menu_rec.h);
	main_menu_rec.w /=3;
	main_menu_rec.h /=3;
	main_menu_rec.x = SCREEN_WIDTH - main_menu_rec.w;
	main_menu_rec.y = (undo_move_rec.y + undo_move_rec.h) + 15;

	//Load QUIT button image as surface
	SDL_Surface* quit_surface = SDL_LoadBMP("./images/game buttons/button-quit.bmp");
	if (!quit_surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT;
	}

	//Create MAIN MENU texture from surface
	SDL_Texture* quit_texture = SDL_CreateTextureFromSurface(renderer, quit_surface);
	if (!quit_texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_FreeSurface(quit_surface);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT;
	}

	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(quit_texture, NULL, NULL, &quit_rec.w, &quit_rec.h);
	quit_rec.w /=3;
	quit_rec.h /=3;
	quit_rec.x = SCREEN_WIDTH - quit_rec.w;
	quit_rec.y = (main_menu_rec.y + main_menu_rec.h) + 15;


	SDL_RenderCopy(renderer, restart_game_texture, NULL, &restart_game_rec);

	SDL_RenderCopy(renderer, load_game_texture, NULL, &load_game_rec);

	SDL_RenderCopy(renderer, save_game_texture, NULL, &save_game_rec);

	SDL_RenderCopy(renderer, undo_move_texture, NULL, &undo_move_rec);

	SDL_RenderCopy(renderer, main_menu_texture, NULL, &main_menu_rec);

	SDL_RenderCopy(renderer, quit_texture, NULL, &quit_rec);

	//show what was drawn on screen
//	SDL_RenderPresent(renderer);

	return GAME_SCREEN;
}


screen display_game_board(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_Surface* game_board_surface = SDL_LoadBMP("./images/Diagramkit V2-5/Boards & Arrays/empty-numbered-chess-set.bmp");
	if (!game_board_surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT;
	}

	//Create RESTART GAME texture from surface
	SDL_Texture* game_board_texture = SDL_CreateTextureFromSurface(renderer, game_board_surface);
	if (!game_board_texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_FreeSurface(game_board_surface);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT;
	}

	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(game_board_texture, NULL, NULL, &game_board_rec.w, &game_board_rec.h);
	game_board_rec.w *= 0.8;
	game_board_rec.h *= 0.8;

	SDL_RenderCopy(renderer, game_board_texture, NULL, &game_board_rec);
//	SDL_RenderPresent(renderer);
	SDL_Log("Finished display_game_board\n");
	return GAME_SCREEN;
}

screen game_screen(SDL_Window* window, SDL_Renderer* renderer, game* game) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
	SDL_RenderClear(renderer);
	screen display_screen;
	SDL_Log("game mode is %d\n", game->game_mode);
	display_screen = display_game_buttons(window, renderer);
	SDL_Log("Between displays\n");
	display_screen = display_game_board(window, renderer);
	SDL_RenderPresent(renderer);
	bool game_running = true;
	while(game_running) {
		SDL_Event event;
		//loop runs as long as event queue isn't empty
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				game_running = false;
				return EXIT;
			case SDL_MOUSEBUTTONUP:
				if (check_mouse_button_event(event, quit_rec)) {
					game_running = false;
					return EXIT;
				} else if (check_mouse_button_event(event, restart_game_rec)) {
					//TODO
				} else if (check_mouse_button_event(event, load_game_rec)) {
					//TODO
				} else if (check_mouse_button_event(event, save_game_rec)) {
					//TODO
				} else if (check_mouse_button_event(event, undo_move_rec)) {
					//TODO
				} else if (check_mouse_button_event(event, main_menu_rec)) {
					game_running = false;
				}
			}
		}

	}

	return display_screen;
}
