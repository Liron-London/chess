/*
 * GUI.c
 *
 *  Created on: Sep 8, 2017
 *      Author: lironl
 */
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "GUI_base.h"
#include "GUI_display_game.h"

//#include <SDL2/SDL_video.h>
//#include <SDL2/SDL_timer.h>
/*
int start_game(SDL_Window* window, SDL_Renderer* rend) {
	display_game_buttons(window, rend);
}
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

int set_difficulty_dialog(game* new_game) {
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
		return 1;
	}
	if (buttonid == -1) {
		SDL_Log("no selection");
	} else if (buttonid <= 3) {
		SDL_Log("selection was %s", buttons[buttonid].text);
		new_game->difficulty = buttonid + 1;
		SDL_Log("Game difficulty is %d", new_game->difficulty);
	}
	return 0;
}

int set_game_mode_dialog(game* new_game) {
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
		return 1;
	}
	if (buttonid == -1) {
		SDL_Log("no selection");
		SDL_Log("Game mode is %d", new_game->game_mode);
	} else if (buttonid == 0) {
		SDL_Log("selection was %s", buttons[buttonid].text);
		new_game->game_mode = 1;
		set_difficulty_dialog(new_game);
	} else if (buttonid == 1) {
		SDL_Log("selection was %s", buttons[buttonid].text);
		new_game->game_mode = 2;
	}
	return 0;
}


//int main(int argc, char* argv[]) {
int main() {
	game* new_game = game_create();
	//Start SDL
//	SDL_Init(SDL_INIT_EVERYTHING);
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


	//Load NEW GAME button image as surface
	SDL_Surface* new_game_surface = SDL_LoadBMP("./images/game buttons/button-new-game.bmp");
	if (!new_game_surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create NEW GAME texture from surface
	SDL_Texture* new_game_texture = SDL_CreateTextureFromSurface(renderer, new_game_surface);
	SDL_FreeSurface(new_game_surface);
	if (!new_game_texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create rectangle
	SDL_Rect new_game_rec = { .x = 0, .y = 30, .w = 600, .h = 600};

	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(new_game_texture, NULL, NULL, &new_game_rec.w, &new_game_rec.h);
	new_game_rec.x = (SCREEN_WIDTH - new_game_rec.w) / 2;
	//	new_game_rec.y = (SCREEN_HEIGHT + new_game_rec.h) + 30;


	//Load LOAD GAME button image as surface
	SDL_Surface* load_game_surface = SDL_LoadBMP("./images/game buttons/button-load-game.bmp");
	if (!load_game_surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create NEW GAME texture from surface
	SDL_Texture* load_game_texture = SDL_CreateTextureFromSurface(renderer, load_game_surface);
	SDL_FreeSurface(load_game_surface);
	if (!load_game_texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create rectangle
	SDL_Rect load_game_rec = { .x = 0, .y = 0, .w = 600, .h = 600};

	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(load_game_texture, NULL, NULL, &load_game_rec.w, &load_game_rec.h);
	load_game_rec.x = (SCREEN_WIDTH - load_game_rec.w) / 2;
	load_game_rec.y = new_game_rec.y + 30 + new_game_rec.h;

	//Load QUIT button image as surface
	SDL_Surface* quit_surface = SDL_LoadBMP("./images/game buttons/button-quit.bmp");
	if (!quit_surface) {
		printf("Error creating SDL surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create texture from surface
	SDL_Texture* quit_texture = SDL_CreateTextureFromSurface(renderer, quit_surface);
	SDL_FreeSurface(quit_surface);
	if (!quit_texture) {
		printf("Error creating SDL texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Create rectangle for button
	SDL_Rect quit_rec = { .x = 0, .y = 0, .w = 50, .h = 50};

	//updates the rectangle to fit the texture dimensions
	SDL_QueryTexture(quit_texture, NULL, NULL, &quit_rec.w, &quit_rec.h);
	quit_rec.x = (SCREEN_WIDTH - quit_rec.w) / 2;
	quit_rec.y = load_game_rec.y + 30 + load_game_rec.h;

	bool running = true;
	while(running) {
		SDL_Event event;
		//loop runs as long as event queue isn't empty
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_MOUSEBUTTONUP:
				if (check_mouse_button_event(event, quit_rec)) {
					running = false;
				}
				else if (check_mouse_button_event(event, new_game_rec)) {
					set_game_mode_dialog(new_game);
				}
				else if (check_mouse_button_event(event, load_game_rec)) {
					running = false;
				}
				break;
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
		/*

    //Apply image to screen
    SDL_BlitSurface( hello, NULL, screen, NULL );

    //Update Screen
    SDL_Flip( screen );

    //Free the loaded image
    SDL_FreeSurface( hello );
		 */

	}

	//Free resources
	SDL_DestroyTexture(new_game_texture);
//	SDL_FreeSurface(new_game_surface);

	SDL_DestroyTexture(load_game_texture);
//	SDL_FreeSurface(load_game_surface);

	SDL_DestroyTexture(quit_texture);
//	SDL_FreeSurface(quit_surface);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//Quit SDL
	SDL_Quit();
	game_destroy(new_game);
	return 0;
}
