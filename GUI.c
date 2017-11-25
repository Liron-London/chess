/*
 * GUI.c
 *
 *  Created on: Sep 8, 2017
 *      Author: lironl
 */
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "GUI.h"
#include "GUI_base.h"
#include "GUI_load.h"
#include "GUI_display_game.h"

//#include <SDL2/SDL_video.h>
//#include <SDL2/SDL_timer.h>


screen set_game_mode_dialog(game* new_game);
screen set_difficulty_dialog(game* new_game);

/*
 * Presents a pop-up message, asking the user to set the game's user color
 * sets the user color accordingly
 */
screen set_user_color_dialog(game* new_game) {
	const SDL_MessageBoxButtonData buttons[] = {
			{ /* .flags, .buttonid, .text */        0, 0, "black"},
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "white"},
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 2, "back"}
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
			"Setting New Game", /* .title */
			"Please select user color", /* .message */
			SDL_arraysize(buttons), /* .numbuttons */
			buttons, /* .buttons */
			&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
		return EXIT;
	} else if (buttonid == 0) {
		new_game->user_color = 0;
		new_game->current_turn = 0;
		return GAME_SCREEN;
	} else if (buttonid == 1) {
		new_game->user_color = 1;
		new_game->current_turn = 1;
		return GAME_SCREEN;
	} else {
		return set_difficulty_dialog(new_game);
	}
	return MENU_SCREEN;
}

/*
 * Presents a pop-up message, asking the user to set the game's difficulty level
 * sets the difficulty level accordingly
 */
screen set_difficulty_dialog(game* new_game) {
	const SDL_MessageBoxButtonData buttons[] = {
			{ /* .flags, .buttonid, .text */        0, 0, "noob" },
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "easy" },
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 2, "moderate" },
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 3, "hard" },
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 4, "back" }
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
					{   123,   182, 86 },
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
					{ 153,   255, 255 }
			}
	};
	const SDL_MessageBoxData messageboxdata = {
			SDL_MESSAGEBOX_INFORMATION, /* .flags */
			NULL, /* .window */
			"Setting New Game", /* .title */
			"Please select difficulty level", /* .message */
			SDL_arraysize(buttons), /* .numbuttons */
			buttons, /* .buttons */
			&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
		return EXIT;
	}
	if (buttonid == -1) {
		SDL_Log("no selection");
	} else if (buttonid <= 3) {
		new_game->difficulty = buttonid + 1;
		return set_user_color_dialog(new_game);
	} else {
		return set_game_mode_dialog(new_game);
	}
	return MENU_SCREEN;
}

/*
 * Presents a pop-up message, asking the user to set the game's game mode
 * sets the game mode accordingly
 */
screen set_game_mode_dialog(game* new_game) {
	const SDL_MessageBoxButtonData buttons[] = {
			{ /* .flags, .buttonid, .text */        0, 0, "1 player" },
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "2 players" },
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 2, "back" }
	};
	const SDL_MessageBoxColorScheme colorScheme = {
			{ /* .colors (.r, .g, .b) */
					/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
					{ 255,   255,   255 },
					/* [SDL_MESSAGEBOX_COLOR_TEXT] */
					{   50, 50,   50 },
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
					{ 123, 182,   86 },
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
					{   123,   182, 86 },
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
					{ 153,   255, 255 }
			}
	};
	const SDL_MessageBoxData messageboxdata = {
			SDL_MESSAGEBOX_INFORMATION, /* .flags */
			NULL, /* .window */
			"Setting New Game", /* .title */
			"Please select game mode", /* .message */
			SDL_arraysize(buttons), /* .numbuttons */
			buttons, /* .buttons */
			&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
		return EXIT;
	}
	if (buttonid == -1) {
		SDL_Log("no selection");
	} else if (buttonid == 0) {
		new_game->game_mode = 1;
		return set_difficulty_dialog(new_game);
	} else if (buttonid == 1) {
		new_game->game_mode = 2;
		return GAME_SCREEN;
	}
	return MENU_SCREEN;
}

/*
 * Presents the main menu buttons and handles them
 * returns what screen needs to be presented: EXIT if an error occured / QUIT was clicked, GAME SCREEN if the user finished
 * setting all the relevant settings, LOAD SCREEN if LOAD was clicked
 */
screen display_main_menu(SDL_Window* window, SDL_Renderer* renderer, game* new_game) {
	screen display_screen = MENU_SCREEN;

	//Load NEW GAME button image as surface
	SDL_Surface* new_game_surface = SDL_LoadBMP("./images/game buttons/button-new-game.bmp");
	display_screen = verify_surface(window, renderer, new_game_surface, MENU_SCREEN);

	SDL_Texture* new_game_texture = SDL_CreateTextureFromSurface(renderer, new_game_surface);
	display_screen = verify_texture(window, renderer, new_game_surface, new_game_texture, MENU_SCREEN);

	SDL_Rect new_game_rec = { .x = 0, .y = 30, .w = 600, .h = 600};
	SDL_QueryTexture(new_game_texture, NULL, NULL, &new_game_rec.w, &new_game_rec.h);
	new_game_rec.x = (SCREEN_WIDTH - new_game_rec.w) / 2;
	//	new_game_rec.y = (SCREEN_HEIGHT + new_game_rec.h) + 30;


	//Load LOAD GAME button image as surface
	SDL_Surface* load_game_surface = SDL_LoadBMP("./images/game buttons/button-load-game.bmp");
	display_screen = verify_surface(window, renderer, load_game_surface, MENU_SCREEN);

	SDL_Texture* load_game_texture = SDL_CreateTextureFromSurface(renderer, load_game_surface);
	display_screen = verify_texture(window, renderer, load_game_surface, load_game_texture, MENU_SCREEN);

	SDL_Rect load_game_rec = { .x = 0, .y = 0, .w = 600, .h = 600};
	SDL_QueryTexture(load_game_texture, NULL, NULL, &load_game_rec.w, &load_game_rec.h);
	load_game_rec.x = (SCREEN_WIDTH - load_game_rec.w) / 2;
	load_game_rec.y = new_game_rec.y + 30 + new_game_rec.h;

	//Load QUIT button image as surface
	SDL_Surface* quit_surface = SDL_LoadBMP("./images/game buttons/button-quit.bmp");
	display_screen = verify_surface(window, renderer, quit_surface, MENU_SCREEN);

	SDL_Texture* quit_texture = SDL_CreateTextureFromSurface(renderer, quit_surface);
	display_screen = verify_texture(window, renderer, quit_surface, quit_texture, MENU_SCREEN);

	SDL_Rect quit_rec = { .x = 0, .y = 0, .w = 50, .h = 50};
	SDL_QueryTexture(quit_texture, NULL, NULL, &quit_rec.w, &quit_rec.h);
	quit_rec.x = (SCREEN_WIDTH - quit_rec.w) / 2;
	quit_rec.y = load_game_rec.y + 30 + load_game_rec.h;

	bool main_menu = true;
	while(main_menu) {
		SDL_Event event;
		//loop runs as long as event queue isn't empty
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				main_menu = false;
				return EXIT;
			case SDL_MOUSEBUTTONUP:
				if (check_mouse_button_event(event, quit_rec)) {
					main_menu = false;
					return EXIT;
				}
				else if (check_mouse_button_event(event, new_game_rec)) {
					return set_game_mode_dialog(new_game);
				}
				else if (check_mouse_button_event(event, load_game_rec)) {
					main_menu = false;
					return LOAD_SCREEN;
				}
			}
		}

		//change renderer background color to white
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);

		//clear screen
		SDL_RenderClear(renderer);

		//Add NEW GAME button
		SDL_RenderCopy(renderer, new_game_texture, NULL, &new_game_rec);
		//Add LOAD GAME button
		SDL_RenderCopy(renderer, load_game_texture, NULL, &load_game_rec);
		//Add QUIT button
		SDL_RenderCopy(renderer, quit_texture, NULL, &quit_rec);

		//show what was drawn on screen
		SDL_RenderPresent(renderer);
	}

	//Free resources
	SDL_DestroyTexture(new_game_texture);

	SDL_DestroyTexture(load_game_texture);

	SDL_DestroyTexture(quit_texture);
	return display_screen;
}

//int main(int argc, char* argv[]) {
int gui() {
	//Start SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		printf("ERROR: unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	//Set up screen
	SDL_Window* window = SDL_CreateWindow("Chess",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			800, 600,
			SDL_WINDOW_OPENGL);
	//Handle error in window creation
	if (!window) {
		printf("Error creating SDL window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	//create a renderer, accelerated and in sync with display refresh rate
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//Handle error in renderer creation
	if (!renderer) {
		printf("Error creating SDL renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	game* new_game = game_create();
	screen running = MENU_SCREEN;
	while(running != EXIT) {
		SDL_Event event;
		//loop runs as long as event queue isn't empty
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				running = EXIT;
				break;
			}
		}

		if (running == MENU_SCREEN) {
			running = display_main_menu(window, renderer, new_game);
		}
		if (running == GAME_SCREEN) {
			running = game_screen(window, renderer, new_game);
//			game_destroy(new_game);
		}
		else if (running == LOAD_SCREEN) {
			running = loading_screen(window, renderer, MENU_SCREEN, new_game);
//			running = game_screen(window, renderer, new_game);
		}
	}
	//free resources
	game_destroy(new_game);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//Quit SDL
	SDL_Quit();
	return 0;
}
