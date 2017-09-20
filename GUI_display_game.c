/*
 * GUI_display_game.c
 *
 *  Created on: Sep 12, 2017
 *      Author: liron
 */
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
//#include <SDL2/SDL.h>
#include "array_list.h"
#include "GUI_base.h"
#include "GUI_display_game.h"
#include "game.h"
#include "game_commands.h"
#include "moves.h"
#include "minimax.h"
#define CELL_WIDTH (65)
#define CELL_HEIGHT (65)
#define BOARD_WIDTH (600)
#define BOARD_HEIGHT (600)
#define ORIGIN_X (72)
#define ORIGIN_Y (527)
//old ORIGIN_Y = 463
// speed in pixels/second
#define SPEED (300)
SDL_Rect restart_game_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect save_game_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect load_game_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect undo_move_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect main_menu_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect quit_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
SDL_Rect game_board_rec = { .x = 0, .y = 0, .w = 600, .h = 600};
gui_piece white_grid[16];
gui_piece black_grid[16];

game* undo_move (array_list* history, game* game) {
	if (history->actualSize == 0) {
		return game;
	}
	move* tmp_move = create_move();
	tmp_move = array_list_get_last_move(history);
	announce_undo_move(current_turn_color(game), tmp_move);
	array_list_remove_last(history);

	tmp_move = array_list_get_last_move(history);
	announce_undo_move((current_turn_color(game)+1)%2, tmp_move);
	game = array_list_get_last_game(history);
	array_list_remove_last(history);

	//updating game and history
	destroy_move(tmp_move);
	return game;
}

void update_history(move* move, game* game, array_list* history) {
	// update history

	if (array_list_is_full(history) == true){
		array_list_remove_first(history);
	}
	array_list_add_last(history, game_copy(game), copy_move(move));
}

//save_rec, load_game_rec, undo_move_rec, main_menu_rec, quit_rec;
screen drag_piece(SDL_Window* window, SDL_Renderer* renderer, game* cur_game, SDL_Rect dest, int moving_rect_color, int moving_rect_idx, int history_size) {
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	SDL_Log("Mouse state: x=%d, y=%d", mouse_x, mouse_y);
	screen display_screen = GAME_SCREEN;

	SDL_Texture* tex;
	if(moving_rect_color == 1) {
		tex = white_grid[moving_rect_idx].texture;
	} else {
		tex = black_grid[moving_rect_idx].texture;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
	SDL_RenderClear(renderer);
	display_screen = display_game_buttons(window, renderer, history_size);
	display_screen = display_game_board(window, renderer);

	for (int i = 0; i < 16; i++) {
		if (cur_game->whites[i]->alive && (moving_rect_color == 0 || moving_rect_idx != i)) {
			SDL_RenderCopy(renderer, white_grid[i].texture, NULL, &white_grid[i].rect);
		}
		if (cur_game->blacks[i]->alive && (moving_rect_color == 1 || moving_rect_idx != i)) {
			SDL_RenderCopy(renderer, black_grid[i].texture, NULL, &black_grid[i].rect);
		}
	}

	// start sprite in center of screen
	//	float x_pos = (BOARD_WIDTH - dest.w) / 2;
	//	//	float y_pos = (BOARD_HEIGHT - dest.h) / 2;
	//	float x_pos = dest.x;
	//	float y_pos = dest.y;
	//	float x_vel = 0;
	//	float y_vel = 0;
	//
	//	// determine velocity toward mouse
	//	int target_x = mouse_x - dest.w / 2;
	//	int target_y = mouse_y - dest.h / 2;
	//	float delta_x = target_x - x_pos;
	//	float delta_y = target_y - y_pos;
	//	float distance = sqrt(delta_x * delta_x + delta_y * delta_y);
	//	SDL_Log("distance is %f", distance);
	//
	//	// prevent jitter
	//	if (distance < 5)
	//	{
	//		x_vel = y_vel = 0;
	//	}
	//	else
	//	{
	//		x_vel = delta_x * SPEED / distance;
	//		y_vel = delta_y * SPEED / distance;
	////		SDL_Log("x_vel is %f, y_vel is %f", x_vel, y_vel);
	//
	//	}
	//
	//	// update positions
	//	x_pos += x_vel / 60;
	//	y_pos += y_vel / 60;
	//
	//	// collision detection with bounds
	//	if (x_pos <= 0) x_pos = 0;
	//	if (y_pos <= 0) y_pos = 0;
	//	if (x_pos >= BOARD_WIDTH - dest.w) x_pos = BOARD_WIDTH - dest.w;
	//	if (y_pos >= BOARD_HEIGHT - dest.h) y_pos = BOARD_HEIGHT - dest.h;
	//	dest.x = x_pos;
	//	dest.y = y_pos;
	dest.x = mouse_x - dest.w / 2;
	dest.y = mouse_y - dest.h / 2;
	SDL_RenderCopy(renderer, tex, NULL, &dest);
	SDL_Log("copied rect with x=%d, y=%d", dest.x, dest.y);
	SDL_RenderPresent(renderer);

	return display_screen;
}


void restart_game(game* cur_game) {
	game* new_game = game_create();

	// copying board
	for (int i=0; i<8; i++){
		for (int j=0; j<8; j++){
			cur_game->board[i][j] = new_game->board[i][j];
		}
	}

	for (int i=0; i<16; i++){
		cur_game->whites[i]->alive = new_game->whites[i]->alive;
		cur_game->whites[i]->color = new_game->whites[i]->color;
		cur_game->whites[i]->piece_location->row = new_game->whites[i]->piece_location->row;
		cur_game->whites[i]->piece_location->column = new_game->whites[i]->piece_location->column;
		cur_game->whites[i]->piece_type = new_game->whites[i]->piece_type;

		cur_game->blacks[i]->alive = new_game->blacks[i]->alive;
		cur_game->blacks[i]->color = new_game->blacks[i]->color;
		cur_game->blacks[i]->piece_location->row = new_game->blacks[i]->piece_location->row;
		cur_game->blacks[i]->piece_location->column = new_game->blacks[i]->piece_location->column;
		cur_game->blacks[i]->piece_type = new_game->blacks[i]->piece_type;
	}

	game_destroy(new_game);
}

int update_pieces_rects(game* cur_game) {
	int x_0 = ORIGIN_X;
	int y_0 = ORIGIN_Y - CELL_HEIGHT;
	//whites
	for (int i = 0; i < 16; i++) {
		if (cur_game->whites[i]->alive) {
			int piece_row = cur_game->whites[i]->piece_location->row;
			int piece_col = cur_game->whites[i]->piece_location->column;
			white_grid[i].rect.x = x_0 + piece_col * CELL_WIDTH;
			white_grid[i].rect.y = y_0 - piece_row * CELL_HEIGHT;
		} else {
			white_grid[i].rect.x = BOARD_WIDTH;
			white_grid[i].rect.y = BOARD_HEIGHT;
		}
	}
	//blacks
	for (int i = 0; i < 16; i++) {
		if (cur_game->blacks[i]->alive) {
			int piece_row = cur_game->blacks[i]->piece_location->row;
			int piece_col = cur_game->blacks[i]->piece_location->column;
			black_grid[i].rect.x = x_0 + piece_col * CELL_WIDTH;
			black_grid[i].rect.y = y_0 - piece_row * CELL_HEIGHT;
		} else {
			black_grid[i].rect.x = BOARD_WIDTH;
			black_grid[i].rect.y = BOARD_HEIGHT;
		}
	}
	SDL_Log("Exiting render_current_game");
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


screen display_game_buttons(SDL_Window* window, SDL_Renderer* renderer, int history_size) {
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
	SDL_Surface* undo_move_surface;
	if (history_size > 0) {
		undo_move_surface = SDL_LoadBMP("./images/game buttons/button-undo-move.bmp");
	} else {
		undo_move_surface = SDL_LoadBMP("./images/game buttons/undo-disabled-button.bmp");
	}
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

screen render_game_screen(SDL_Window* window, SDL_Renderer* renderer, game* cur_game, int history_size) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
	SDL_RenderClear(renderer);
	screen display_screen;
	display_screen = display_game_buttons(window, renderer, history_size);
	display_screen = display_game_board(window, renderer);
	//	initialize_pieces(window, renderer);
	for (int i = 0; i < 16; i++) {
		if (cur_game->whites[i]->alive) {
			SDL_RenderCopy(renderer, white_grid[i].texture, NULL, &white_grid[i].rect);
		}
		if (cur_game->blacks[i]->alive) {
			SDL_RenderCopy(renderer, black_grid[i].texture, NULL, &black_grid[i].rect);
		}
	}
	SDL_RenderPresent(renderer);
	return display_screen;
}

screen game_screen(SDL_Window* window, SDL_Renderer* renderer, game* game) {
	screen display_screen = GAME_SCREEN;
	move* new_move = create_move();
	array_list* history = array_list_create(6); //need to free later
	display_screen = initialize_pieces(window, renderer);
	display_screen = render_game_screen(window, renderer, game, history->actualSize);
	int mouse_x, mouse_y;
	bool click = false;
	int moving_rect_idx;
	int moving_rect_color; //0 black, 1 white
	SDL_Rect dest;

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
				if (mouse_x <= BOARD_WIDTH && mouse_y <= BOARD_HEIGHT && click == false) {
					mouse_location_on_board(mouse_x, mouse_y, new_move->source);

					// get cursor position relative to window

					for(int i = 0; i < 16; i++) {
						if (check_mouse_button_event(event, white_grid[i].rect)) {
							SDL_Log("in if -> white grid");
							dest = white_grid[i].rect;
							moving_rect_idx = i;
							moving_rect_color = 1;
							break;
						} else if (check_mouse_button_event(event, black_grid[i].rect)) {
							SDL_Log("in if -> black grid");
							dest = black_grid[i].rect;
							moving_rect_idx = i;
							moving_rect_color = 0;
							break;
						}
					}
					click = true;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				click = false;
				SDL_Log("button up event");
				//checking if mouse was released within game board
				mouse_x = event.button.x;
				mouse_y = event.button.y;
				if (mouse_x <= BOARD_WIDTH && mouse_y <= BOARD_HEIGHT) {
					mouse_location_on_board(mouse_x, mouse_y, new_move->dest);
					SDL_Log("current turn is %d, user color is %d", game->current_turn, game->user_color);
					click = false;
					if (is_valid_move(game, new_move)) {
						if (game->game_mode == 1){
							update_history(new_move, game, history);
							SDL_Log("history's size is %d", history->actualSize);
						}
						piece* cur_piece = location_to_piece(game, new_move->source);
						move_piece(game, new_move, cur_piece);
						print_board(game);
						// update history
					}
					update_pieces_rects(game);
					render_game_screen(window, renderer, game, history->actualSize);
				}
				//checking buttons
				else if (check_mouse_button_event(event, quit_rec)) {
					SDL_Log("clicked on QUIT");
					game_running = false;
					return EXIT;
				} else if (check_mouse_button_event(event, restart_game_rec)) {
					restart_game(game);
					update_pieces_rects(game);
					render_game_screen(window, renderer, game, history->actualSize);
				} else if (check_mouse_button_event(event, load_game_rec)) {
					//TODO
				} else if (check_mouse_button_event(event, save_game_rec)) {
					//TODO
				} else if (check_mouse_button_event(event, undo_move_rec)) {
					game = undo_move(history, game);
					SDL_Log("current turn is player %d", game->current_turn);
					update_pieces_rects(game);
					render_game_screen(window, renderer, game, history->actualSize);
				} else if (check_mouse_button_event(event, main_menu_rec)) {
					game_running = false;
				}
			}
		}
		if (click) {
			drag_piece(window, renderer, game, dest, moving_rect_color, moving_rect_idx, history->actualSize);
		}
		// computer's turn
		if (game->game_mode == 1 && game->current_turn == 0){
			move* comp_move;
			comp_move = get_recommended_move_for_comp(game, game->difficulty);
			//			announce_computer_move(game, comp_move);
			move_piece(game, comp_move, location_to_piece(game, comp_move->source));
			print_board(game);
			update_pieces_rects(game);
			render_game_screen(window, renderer, game, history->actualSize);
			// update history
			update_history(comp_move, game, history);
			SDL_Log("history's size is %d", history->actualSize);
			destroy_move(comp_move);

		}
	}
	//free all resources
	destroy_move(new_move);
	array_list_destroy(history);
	SDL_Log("finished outer while loop");
	for (int i = 0; i < 16; i++) {
		SDL_DestroyTexture(white_grid[i].texture);
		SDL_DestroyTexture(black_grid[i].texture);
	}

	return display_screen;
}
