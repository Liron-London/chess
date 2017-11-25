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
#include "GUI_load.h"
#include "game.h"
#include "game_commands.h"
#include "moves.h"
#include "minimax.h"
#include "file_handler.h"

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

void initialize_rects() ;

screen popup_save(game* game) {
	const SDL_MessageBoxButtonData buttons[] = {
			{ /* .flags, .buttonid, .text */ 0, 0, "Yes"},
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "No"},
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 2, "Cancel"}
	};
	const SDL_MessageBoxColorScheme colorScheme = {
			{ /* .colors (.r, .g, .b) */
					/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
					{255, 255, 255},
					/* [SDL_MESSAGEBOX_COLOR_TEXT] */
					{50, 50, 50},
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
					{123, 182, 86},
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
					{123, 182, 86},
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
					{153, 255, 255}
			}
	};
	const SDL_MessageBoxData messageboxdata = {
			SDL_MESSAGEBOX_INFORMATION, /* .flags */
			NULL, /* .window */
			"Are you sure?", /* .title */
			"Would you like to save your current game before exiting?", /* .message */
			SDL_arraysize(buttons), /* .numbuttons */
			buttons, /* .buttons */
			&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
		return EXIT;
	} else if (buttonid == 0) {
		int num_games = get_num_games();
		default_save(game, num_games);
		return EXIT;
	} else if (buttonid == 1) {
		return EXIT;
	} else if (buttonid == 2) {
		return GAME_SCREEN;
	}
	return MENU_SCREEN;
}

/*
 * Presents a pop-up message when the game ends with mate and informs who won
 * Returns the screen that needs to be presented - EXIT if an error occurred, MAIN MENU by default
 */
screen popup_mate(int color) {
	char message[40];
	if (color == 1) {
		sprintf(message, "Game over - white player wins the game!");
	} else {
		sprintf(message, "Game over - black player wins the game!");
	}

	const SDL_MessageBoxButtonData buttons[] = {
			{ /* .flags, .buttonid, .text */        0, 0, "OK"}
	};
	const SDL_MessageBoxColorScheme colorScheme = {
			{ /* .colors (.r, .g, .b) */
					/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
					{255, 255, 255},
					/* [SDL_MESSAGEBOX_COLOR_TEXT] */
					{50, 50, 50},
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
					{123, 182, 86},
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
					{123, 182, 86},
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
					{153, 255, 255}
			}
	};
	const SDL_MessageBoxData messageboxdata = {
			SDL_MESSAGEBOX_INFORMATION, /* .flags */
			NULL, /* .window */
			"Game Over", /* .title */
			message, /* .message */
			SDL_arraysize(buttons), /* .numbuttons */
			buttons, /* .buttons */
			&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
		return EXIT;
	}
	return MENU_SCREEN;
}

/*
 * Presents a pop-up message when the game ends with a tie
 * Returns the screen that needs to be presented - EXIT if an error occurred, MAIN MENU by default
 */
screen popup_tie() {
	const SDL_MessageBoxButtonData buttons[] = {
			{ /* .flags, .buttonid, .text */        0, 0, "OK"}
	};
	const SDL_MessageBoxColorScheme colorScheme = {
			{ /* .colors (.r, .g, .b) */
					/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
					{255, 255, 255},
					/* [SDL_MESSAGEBOX_COLOR_TEXT] */
					{50, 50, 50},
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
					{123, 182, 86},
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
					{123, 182, 86},
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
					{153, 255, 255}
			}
	};
	const SDL_MessageBoxData messageboxdata = {
			SDL_MESSAGEBOX_INFORMATION, /* .flags */
			NULL, /* .window */
			"Game Over", /* .title */
			"The game ends in a tie", /* .message */
			SDL_arraysize(buttons), /* .numbuttons */
			buttons, /* .buttons */
			&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
		return EXIT;
	}
	return MENU_SCREEN;
}

/*
 * Presents a pop-up message when the game reaches "check" and informs which king is threatened
 * Returns the screen that needs to be presented - EXIT if an error occurred, MAIN MENU by default
 */
screen popup_check(int color) {
	char message[40];
	if (color == 1) {
		sprintf(message, "Check: white King is threatened!");
	} else {
		sprintf(message, "Check: black King is threatened!");
	}

	const SDL_MessageBoxButtonData buttons[] = {
			{ /* .flags, .buttonid, .text */        0, 0, "OK"}
	};
	const SDL_MessageBoxColorScheme colorScheme = {
			{ /* .colors (.r, .g, .b) */
					/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
					{255, 255, 255},
					/* [SDL_MESSAGEBOX_COLOR_TEXT] */
					{50, 50, 50},
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
					{123, 182, 86},
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
					{123, 182, 86},
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
					{153, 255, 255}
			}
	};
	const SDL_MessageBoxData messageboxdata = {
			SDL_MESSAGEBOX_INFORMATION, /* .flags */
			NULL, /* .window */
			"Check", /* .title */
			message, /* .message */
			SDL_arraysize(buttons), /* .numbuttons */
			buttons, /* .buttons */
			&colorScheme /* .colorScheme */
	};

	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
		return EXIT;
	}
	return GAME_SCREEN;
}

/*
 * checks for check / mate / tie
 * displays popup message if needed (by calling popup_X())
 * returns EXIT screen if mate or tie, GAME_SCREEN if check or none
 */
screen check_game_status(game* game) {
	screen display_screen = GAME_SCREEN;
	int color = current_turn_color(game);
	if (has_valid_moves(game) == false) {
		change_turn(game);
		if (is_check(game) == true) {
			display_screen = popup_mate(color);
		}
		else {
			display_screen = popup_tie();
		}
	}
	change_turn(game);
	if (is_check(game)) {
		display_screen = popup_check((color + 1)%2);
	}
	change_turn(game);

	return display_screen;
}

/*
 * Called when the UNDO MOVE button is clicked
 * Removes the last 2 elements from the history
 * @Return value: the updates game
 */
game* undo_move (array_list* history, game* game) {
	if (history->actualSize == 0) {
		return game;
	}

	array_list_remove_last(history);

	game = game_copy(array_list_get_last_game(history));
	array_list_remove_last(history);

	return game;
}

/*
 * Adds the move&game to the last history element
 * if history is full before adding - removes the oldest element from history to make room
 */
void update_history(move* move, game* game, array_list* history) {

	if (array_list_is_full(history) == true){
		array_list_remove_first(history);
	}
	array_list_add_last(history, game_copy(game), copy_move(move));
}

/*
 *  Given a 'dest' Rect param, makes it follow the cursor by re-rendering the screen
 *  @Return value: the screen that needs to be displayed - EXIT is an error occurred, GAME_SCREEN by default
 */
screen drag_piece(SDL_Window* window, SDL_Renderer* renderer, game* cur_game, SDL_Rect dest, int moving_rect_color, int moving_rect_idx, int history_size) {
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
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

	dest.x = mouse_x - dest.w / 2;
	dest.y = mouse_y - dest.h / 2;
	SDL_RenderCopy(renderer, tex, NULL, &dest);
	SDL_RenderPresent(renderer);

	return display_screen;
}

/*
 * Called when the RESTART GAME button is clicked
 * given the current game - restarts it (re-initializes its fields), leaving the level, mode and user color unchanged
 */
void restart_game(game* cur_game) {
	initialize_rects();
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
	cur_game->current_turn = new_game->current_turn;

	game_destroy(new_game);
}

/*
 * Called when drag&drop ends (on drop)
 * given the current game - updates the rectangles that hold the pieces to be located according to the game's blacks[] and whites[]
 */
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
	return 0;
}




/*
 * updates the source param to contain the row&column the cursor is positioned on
 */
void mouse_location_on_board(int mouse_x, int mouse_y, location* source) {
	source->row = (ORIGIN_Y - mouse_y) / CELL_HEIGHT;
	source->column = (mouse_x - ORIGIN_X) / CELL_WIDTH;
}

/*
 * makes the rectangle that was clicked on follow the cursor
 */
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

/*
 * Initializes the black/white_grid[]'s rectangles to be outside of the board and in the correct size
 * They are later repositioned by update_pieces_rects
 */
void initialize_rects() {
	for (int i = 0; i < 16; i++) {
		SDL_Rect white_square = {.x = BOARD_WIDTH, .y = BOARD_HEIGHT, .w = CELL_WIDTH, .h = CELL_HEIGHT};
		white_grid[i].rect = white_square;
		SDL_Rect black_square = {.x = BOARD_WIDTH, .y = BOARD_HEIGHT, .w = CELL_WIDTH, .h = CELL_HEIGHT};
		black_grid[i].rect = black_square;
	}
}

/*
 * loads all the pieces' images to the relevant Rects
 */
screen initialize_pieces(SDL_Window* window, SDL_Renderer* renderer){
	initialize_rects();
	//	int x_0 = ORIGIN_X;
	//	int y_0 = ORIGIN_Y - CELL_HEIGHT;
	//	for (int i = 0; i < 16; i++) {
	//		SDL_Rect square = {.x = x_0, .y = y_0, .w = CELL_WIDTH, .h = CELL_HEIGHT};
	//		white_grid[i].rect = square;
	//		x_0 += CELL_WIDTH;
	//		if (i == 7) {
	//			x_0 = ORIGIN_X;
	//			y_0 -= CELL_HEIGHT;
	//		}
	//	}


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

	//	x_0 = ORIGIN_X;
	//	y_0 = ORIGIN_Y - 8 * CELL_HEIGHT;
	//	for (int i = 0; i < 16; i++) {
	//		SDL_Rect square = {.x = x_0, .y = y_0, .w = CELL_WIDTH, .h = CELL_HEIGHT};
	//		black_grid[i].rect = square;
	//		x_0 += CELL_WIDTH;
	//		if (i == 7) {
	//			x_0 = ORIGIN_X;
	//			y_0 += CELL_HEIGHT;
	//		}
	//	}

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

/*
 * Creates and copies to renderer the GAME SCREEN buttons, enabled/disabled correctly
 * history_size param used for determining if "undo" is enabled
 * @Return value: the screen that needs to be presented - EXIT if an error occurred, GAME_SCREEN by default
 */
screen display_game_buttons(SDL_Window* window, SDL_Renderer* renderer, int history_size) {
	screen display_screen = GAME_SCREEN;

	//RESTART GAME
	SDL_Surface* restart_game_surface = SDL_LoadBMP("./images/game buttons/button-restart.bmp");
	display_screen = verify_surface(window, renderer, restart_game_surface, GAME_SCREEN);

	SDL_Texture* restart_game_texture = SDL_CreateTextureFromSurface(renderer, restart_game_surface);
	display_screen = verify_texture(window, renderer, restart_game_surface, restart_game_texture, GAME_SCREEN);

	SDL_QueryTexture(restart_game_texture, NULL, NULL, &restart_game_rec.w, &restart_game_rec.h);
	restart_game_rec.w /=3;
	restart_game_rec.h /=3;
	restart_game_rec.x = SCREEN_WIDTH - restart_game_rec.w;
	restart_game_rec.y = (restart_game_rec.h) + 30;


	//SAVE GAME
	SDL_Surface* save_game_surface = SDL_LoadBMP("./images/game buttons/button-save.bmp");
	display_screen = verify_surface(window, renderer, save_game_surface, GAME_SCREEN);

	SDL_Texture* save_game_texture = SDL_CreateTextureFromSurface(renderer, save_game_surface);
	display_screen = verify_texture(window, renderer, save_game_surface, save_game_texture, GAME_SCREEN);

	SDL_QueryTexture(save_game_texture, NULL, NULL, &save_game_rec.w, &save_game_rec.h);
	save_game_rec.w /=3;
	save_game_rec.h /=3;
	save_game_rec.x = SCREEN_WIDTH - save_game_rec.w;
	save_game_rec.y = (restart_game_rec.y + restart_game_rec.h) + 15;


	//LOAD GAME
	SDL_Surface* load_game_surface = SDL_LoadBMP("./images/game buttons/button-load-game.bmp");
	display_screen = verify_surface(window, renderer, load_game_surface, GAME_SCREEN);

	SDL_Texture* load_game_texture = SDL_CreateTextureFromSurface(renderer, load_game_surface);
	display_screen = verify_texture(window, renderer, load_game_surface, load_game_texture, GAME_SCREEN);

	SDL_QueryTexture(load_game_texture, NULL, NULL, &load_game_rec.w, &load_game_rec.h);
	load_game_rec.w /=3;
	load_game_rec.h /=3;
	load_game_rec.x = SCREEN_WIDTH - load_game_rec.w;
	load_game_rec.y = (save_game_rec.y + save_game_rec.h) + 15;


	//UNDO MOVE
	SDL_Surface* undo_move_surface;
	if (history_size > 0) {
		undo_move_surface = SDL_LoadBMP("./images/game buttons/button-undo-move.bmp");
	} else {
		undo_move_surface = SDL_LoadBMP("./images/game buttons/undo-disabled-button.bmp");
	}
	display_screen = verify_surface(window, renderer, undo_move_surface, GAME_SCREEN);

	SDL_Texture* undo_move_texture = SDL_CreateTextureFromSurface(renderer, undo_move_surface);
	display_screen = verify_texture(window, renderer, undo_move_surface, undo_move_texture, GAME_SCREEN);

	SDL_QueryTexture(undo_move_texture, NULL, NULL, &undo_move_rec.w, &undo_move_rec.h);
	undo_move_rec.w /=3;
	undo_move_rec.h /=3;
	undo_move_rec.x = SCREEN_WIDTH - undo_move_rec.w;
	undo_move_rec.y = (load_game_rec.y + load_game_rec.h) + 15;

	//MAIN MENU
	SDL_Surface* main_menu_surface = SDL_LoadBMP("./images/game buttons/button-main-menu.bmp");
	display_screen = verify_surface(window, renderer, main_menu_surface, GAME_SCREEN);

	SDL_Texture* main_menu_texture = SDL_CreateTextureFromSurface(renderer, main_menu_surface);
	display_screen = verify_texture(window, renderer, main_menu_surface, main_menu_texture, GAME_SCREEN);

	SDL_QueryTexture(main_menu_texture, NULL, NULL, &main_menu_rec.w, &main_menu_rec.h);
	main_menu_rec.w /=3;
	main_menu_rec.h /=3;
	main_menu_rec.x = SCREEN_WIDTH - main_menu_rec.w;
	main_menu_rec.y = (undo_move_rec.y + undo_move_rec.h) + 15;

	//QUIT
	SDL_Surface* quit_surface = SDL_LoadBMP("./images/game buttons/button-quit.bmp");
	display_screen = verify_surface(window, renderer, quit_surface, GAME_SCREEN);

	SDL_Texture* quit_texture = SDL_CreateTextureFromSurface(renderer, quit_surface);
	display_screen = verify_texture(window, renderer, quit_surface, quit_texture, GAME_SCREEN);

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

	return display_screen;
}

/*
 * Creates the game board image and copies it to the renderer
 */
screen display_game_board(SDL_Window* window, SDL_Renderer* renderer) {
	screen display_screen = GAME_SCREEN;
	SDL_Surface* game_board_surface = SDL_LoadBMP("./images/Diagramkit V2-5/Boards & Arrays/empty-numbered-chess-set.bmp");
	display_screen = verify_surface(window, renderer, game_board_surface, GAME_SCREEN);

	SDL_Texture* game_board_texture = SDL_CreateTextureFromSurface(renderer, game_board_surface);
	display_screen = verify_texture(window, renderer, game_board_surface, game_board_texture, GAME_SCREEN);

	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(game_board_texture, NULL, NULL, &game_board_rec.w, &game_board_rec.h);
	game_board_rec.w = 600;
	game_board_rec.h = 600;

	SDL_RenderCopy(renderer, game_board_texture, NULL, &game_board_rec);
	//	SDL_RenderPresent(renderer);
	return display_screen;
}

/*
 * clears the previous board
 * calls display_game_buttons, display_game_board, updates_pieces_rects
 * copies all the Rects to the renderer
 * presents the renderer
 * @Return value: GAME_SCREEN if all is ok, else EXIT
 */
screen render_game_screen(SDL_Window* window, SDL_Renderer* renderer, game* cur_game, int history_size) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
	SDL_RenderClear(renderer);
	screen display_screen;
	display_screen = display_game_buttons(window, renderer, history_size);
	display_screen = display_game_board(window, renderer);
	//	initialize_pieces(window, renderer);
	update_pieces_rects(cur_game);

	for (int i = 0; i < 16; i++) {
		SDL_RenderCopy(renderer, white_grid[i].texture, NULL, &white_grid[i].rect);
		SDL_RenderCopy(renderer, black_grid[i].texture, NULL, &black_grid[i].rect);
	}

	SDL_RenderPresent(renderer);
	return display_screen;
}

/*
 * Management method of the GAME SCREEN
 * Holds the event loop and manages the game state
 * @Return value: the screen that needs to be presented - EXIT if an error occurred, GAME_SCREEN by default, LOAD / MAIN MENU
 * if the corresponding buttons were clicked
 */
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
				mouse_x = event.button.x;
				mouse_y = event.button.y;
				if (mouse_x <= BOARD_WIDTH && mouse_y <= BOARD_HEIGHT && click == false) {
					mouse_location_on_board(mouse_x, mouse_y, new_move->source);

					// identify what rect was clicked on
					for(int i = 0; i < 16; i++) {
						if (check_mouse_button_event(event, white_grid[i].rect)) {
							dest = white_grid[i].rect;
							moving_rect_idx = i;
							moving_rect_color = 1;
							break;
						} else if (check_mouse_button_event(event, black_grid[i].rect)) {
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
				//checking if mouse was released within game board
				mouse_x = event.button.x;
				mouse_y = event.button.y;
				if (mouse_x <= BOARD_WIDTH && mouse_y <= BOARD_HEIGHT) {
					mouse_location_on_board(mouse_x, mouse_y, new_move->dest);
					click = false;
					if (is_valid_move(game, new_move)) {
						if (game->game_mode == 1){
							update_history(new_move, game, history);
						}
						piece* cur_piece = location_to_piece(game, new_move->source);
						move_piece(game, new_move, cur_piece);
						display_screen = check_game_status(game);
						if (display_screen == MENU_SCREEN) {
							game_running = false;
						}
					}
					//					update_pieces_rects(game);
					render_game_screen(window, renderer, game, history->actualSize);
				}

				//checking buttons
				else if (check_mouse_button_event(event, quit_rec)) {
					display_screen = popup_save(game);
					if (display_screen == EXIT) {
						game_running = false;
						return EXIT;
					}
				} else if (check_mouse_button_event(event, restart_game_rec)) {
					restart_game(game);
					update_pieces_rects(game);
					render_game_screen(window, renderer, game, history->actualSize);
				} else if (check_mouse_button_event(event, load_game_rec)) {
					display_screen = loading_screen(window, renderer, GAME_SCREEN, game);
					initialize_rects();
					render_game_screen(window, renderer, game, 0);
				} else if (check_mouse_button_event(event, save_game_rec)) {
					int num_games = get_num_games();
					default_save(game, num_games);
				} else if (check_mouse_button_event(event, undo_move_rec)) {
					game = undo_move(history, game);
					update_pieces_rects(game);
					render_game_screen(window, renderer, game, history->actualSize);
				} else if (check_mouse_button_event(event, main_menu_rec)) {
					display_screen = popup_save(game);
					if (display_screen == EXIT) {
						game_running = false;
						restart_game(game);
						return MENU_SCREEN;
					}
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
			update_pieces_rects(game);
			render_game_screen(window, renderer, game, history->actualSize);
			// update history
			update_history(comp_move, game, history);
			destroy_move(comp_move);
			display_screen = check_game_status(game);
			if (display_screen == MENU_SCREEN) {
				game_running = false;
			}

		}
	}
	//free all resources
	destroy_move(new_move);
	array_list_destroy(history);
	for (int i = 0; i < 16; i++) {
		SDL_DestroyTexture(white_grid[i].texture);
		SDL_DestroyTexture(black_grid[i].texture);
	}

	return display_screen;
}
