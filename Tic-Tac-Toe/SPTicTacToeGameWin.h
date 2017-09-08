#ifndef SPTICTACTOEGAMEWIN_H_
#define SPTICTACTOEGAMEWIN_H_
#include <SDL.h>
#include <SDL_video.h>
#include "SPTicTacToeWindow.h"
#include "SPTicTacToe.h"

typedef enum {
	SP_GAME_EVENT_X_WON,
	SP_GAME_EVENT_O_WON,
	SP_GAME_EVENT_TIE,
	SP_GAME_EVENT_QUIT,
	SP_GAME_EVENT_INVALID_ARGUMENT,
	SP_GAME_EVENT_NONE
} SP_GAME_EVENT;

typedef struct{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	SDL_Texture* xTexture;
	SDL_Texture* oTexture;
	SPTicTacToe* game;
}SPGameWin;

SPGameWin* spGameWindowCreate();
void spGameWindowDraw(SPGameWin*);
void spGameWindowDestroy(SPGameWin*);
SP_GAME_EVENT spGameWindowHandleEvent(SPGameWin* src, SDL_Event* event);


#endif
