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
#include "game.h"
#include "moves.h"

#define CELL_WIDTH (65)
#define CELL_HEIGHT (65)
#define BOARD_WIDTH (600)
#define BOARD_HEIGHT (600)
#define ORIGIN_X (72)
#define ORIGIN_Y (527)
//old ORIGIN_Y = 463
SDL_Rect restart_game_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect save_game_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect load_game_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect undo_move_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect main_menu_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect quit_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect game_board_rec = { .x = 0, .y = 0, .w = 600, .h = 600};
gui_piece white_grid[16];
gui_piece black_grid[16];

//save_rec, load_game_rec, undo_move_rec, main_menu_rec, quit_rec;

int move_piece_gui(game* cur_game, move* move) {
	int x_0 = ORIGIN_X;
	int y_0 = ORIGIN_Y - CELL_HEIGHT;
	piece* cur_piece = location_to_piece(cur_game, move->source);
	move_piece(cur_game, move, cur_piece);
	print_board(cur_game);
	//whites
	for (int i = 0; i < 16; i++) {
		int piece_row = cur_game->whites[i]->piece_location->row;
		int piece_col = cur_game->whites[i]->piece_location->column;
		white_grid[i].rect.x = x_0 + piece_col * CELL_WIDTH;
		white_grid[i].rect.y = y_0 - piece_row * CELL_HEIGHT;
	}
	//blacks
	for (int i = 0; i < 16; i++) {
		int piece_row = cur_game->blacks[i]->piece_location->row;
		int piece_col = cur_game->blacks[i]->piece_location->column;
		black_grid[i].rect.x = x_0 + piece_col * CELL_WIDTH;
		black_grid[i].rect.y = y_0 - piece_row * CELL_HEIGHT;
	}
	SDL_Log("Exiting move_piece_gui");
	return 0;
}

void mouse_location_on_board(int mouse_x, int mouse_y, location* source) {
	//	SDL_Log("Mouse coordinates are x=%d, y=%d", mouse_x, mouse_y);
	source->row = (ORIGIN_Y - mouse_y) / CELL_HEIGHT;
	source->column = (mouse_x - ORIGIN_X) / CELL_WIDTH;
	SDL_Log("Mouse location is row=%d, col=%d", source->row, source->column);
}

screen draw_piece(SDL_Window* window, SDL_Renderer* renderer, gui_piece* guipiece, char* filename) {
	char fullpath[50];
	char* directory = "./images/Diagramkit V2-5/Figurines/";
	strcpy(fullpath, directory);
	strcat(fullpath, filename);

	SDL_Surface* surface = SDL_LoadBMP(fullpath);
	if (verify_surface(window, renderer, surface, GAME_SCREEN) == EXIT) {
		return EXIT;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (verify_texture(window, renderer, surface, texture, GAME_SCREEN) == EXIT) {
		return EXIT;
	}
	//TODO: destroy surface
	SDL_RenderCopy(renderer, texture, NULL, &guipiece->rect);
	guipiece->texture = texture;
	return GAME_SCREEN;
}

screen initialize_pieces(SDL_Window* window, SDL_Renderer* renderer){
	//	SDL_Surface* black_bishop_surface = SDL_LoadBMP("./images/Diagramkit V2-5/Figurines/Black B.bmp")
	int x_0 = ORIGIN_X;
	int y_0 = ORIGIN_Y - CELL_HEIGHT;
	for (int i = 0; i < 16; i++) {
		SDL_Rect square = {.x = x_0, .y = y_0, .w = CELL_WIDTH, .h = CELL_HEIGHT};
		white_grid[i].rect = square;
		x_0 += CELL_WIDTH;
		if (i == 7) {
			x_0 = ORIGIN_X;
			y_0 -= CELL_HEIGHT;
		}
	}

	//	char* green_pieces[] = {"Green2 B.bmp", "Green2 K.bmp", "Green2 N.bmp", "Green2 P.bmp", "Green2 Q.bmp", "Green2 R.bmp"};
	// draw white pieces
	draw_piece(window, renderer, &white_grid[0], "Green2 R.bmp");
	draw_piece(window, renderer, &white_grid[1], "Green2 N.bmp");
	draw_piece(window, renderer, &white_grid[2], "Green2 B.bmp");
	draw_piece(window, renderer, &white_grid[3], "Green2 Q.bmp");
	draw_piece(window, renderer, &white_grid[4], "Green2 K.bmp");
	draw_piece(window, renderer, &white_grid[5], "Green2 B.bmp");
	draw_piece(window, renderer, &white_grid[6], "Green2 N.bmp");
	draw_piece(window, renderer, &white_grid[7], "Green2 R.bmp");
	for (int idx = 8; idx < 16; idx++) {
		draw_piece(window, renderer, &white_grid[idx], "Green2 P.bmp");
	}

	x_0 = ORIGIN_X;
	y_0 = ORIGIN_Y - 8 * CELL_HEIGHT;
	for (int i = 0; i < 16; i++) {
		SDL_Rect square = {.x = x_0, .y = y_0, .w = CELL_WIDTH, .h = CELL_HEIGHT};
		black_grid[i].rect = square;
		x_0 += CELL_WIDTH;
		if (i == 7) {
			x_0 = ORIGIN_X;
			y_0 += CELL_HEIGHT;
		}
	}
	// draw black pieces
	draw_piece(window, renderer, &black_grid[0], "Black R.bmp");
	draw_piece(window, renderer, &black_grid[1], "Black N.bmp");
	draw_piece(window, renderer, &black_grid[2], "Black B.bmp");
	draw_piece(window, renderer, &black_grid[3], "Black Q.bmp");
	draw_piece(window, renderer, &black_grid[4], "Black K.bmp");
	draw_piece(window, renderer, &black_grid[5], "Black B.bmp");
	draw_piece(window, renderer, &black_grid[6], "Black N.bmp");
	draw_piece(window, renderer, &black_grid[7], "Black R.bmp");
	for (int idx = 8; idx < 16; idx++) {
		draw_piece(window, renderer, &black_grid[idx], "Black P.bmp");
	}
	return GAME_SCREEN;
}


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
	game_board_rec.w = 600;
	game_board_rec.h = 600;

	SDL_RenderCopy(renderer, game_board_texture, NULL, &game_board_rec);
	//	SDL_RenderPresent(renderer);
	return GAME_SCREEN;
}

screen render_game_screen(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
	SDL_RenderClear(renderer);
	screen display_screen;
	display_screen = display_game_buttons(window, renderer);
	display_screen = display_game_board(window, renderer);
//	initialize_pieces(window, renderer);
	for (int i = 0; i < 16; i++) {
		SDL_RenderCopy(renderer, black_grid[i].texture, NULL, &black_grid[i].rect);
		SDL_RenderCopy(renderer, white_grid[i].texture, NULL, &white_grid[i].rect);
	}
	SDL_RenderPresent(renderer);
	return display_screen;
}

screen game_screen(SDL_Window* window, SDL_Renderer* renderer, game* game) {
	screen display_screen = GAME_SCREEN;
	move* new_move = create_move(); //need to free later
	display_screen = initialize_pieces(window, renderer);
	display_screen = render_game_screen(window, renderer);
	int mouse_x, mouse_y;

	bool game_running = true;
	while(game_running) {
		SDL_Event event;
		//loop runs as long as event queue isn't empty
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				game_running = false;
				return EXIT;
			case SDL_MOUSEBUTTONDOWN:
				SDL_Log("button down event");
				mouse_x = event.button.x;
				mouse_y = event.button.y;
				if (mouse_x <= BOARD_WIDTH && mouse_y <= BOARD_HEIGHT) {
					mouse_location_on_board(mouse_x, mouse_y, new_move->source);
				}
				break;
			case SDL_MOUSEBUTTONUP:
				SDL_Log("button up event");
				//checking if mouse was released within game board
				mouse_x = event.button.x;
				mouse_y = event.button.y;
				if (mouse_x <= BOARD_WIDTH && mouse_y <= BOARD_HEIGHT) {
					mouse_location_on_board(mouse_x, mouse_y, new_move->dest);
					SDL_Log("current turn is %d, user color is %d", game->current_turn, game->user_color);
					SDL_Log("new move: source = (%d, %d), dest = (%d, %d)", new_move->source->row, new_move->source->column, new_move->dest->row, new_move->dest->column);
					if (is_valid_move(game, new_move)) {
						move_piece_gui(game, new_move);
						SDL_Log("after move_piece_gui");
						render_game_screen(window, renderer);
					}
				}
				//checking buttons
				else if (check_mouse_button_event(event, quit_rec)) {
					SDL_Log("clicked on QUIT");
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


		//			// determine velocity toward mouse
		//			int target_x = mouse_x - dest.w / 2;
		//			int target_y = mouse_y - dest.h / 2;
		//			float delta_x = target_x - x_pos;
		//			float delta_y = target_y - y_pos;
		//			float distance = sqrt(delta_x * delta_x + delta_y * delta_y);
		//
		//			// prevent jitter
		//			if (distance < 5)
		//			{
		//				x_vel = y_vel = 0;
		//			}
		//			else
		//			{
		//				x_vel = delta_x * SPEED / distance;
		//				y_vel = delta_y * SPEED / distance;
		//			}
		//
		//			// reverse velocity if mouse button 1 pressed



	}

	return display_screen;
}
