#include "SPTicTacToeMainWin.h"
#include <SDL_video.h>
#include <stdio.h>

//Inner functions
int isClickOnStart(int x, int y) {
	if ((x >= 75 && x <= 250) && (y >= 100 && y <= 200)) {
		return 1;
	}
	return 0;
}

int isClickOnExit(int x, int y) {
	if ((x >= 75 && x <= 250) && (y >= 250 && y <= 350)) {
		return 1;
	}
	return 0;
}

SPMainWin* spMainWindowCreate() {
	SPMainWin* res = NULL;
	SDL_Surface* loadingSurface = NULL;
	res = (SPMainWin*) calloc(sizeof(SPMainWin), sizeof(char));
	if (res == NULL ) {
		return NULL ;
	}

	// Create an application window with the following settings:
	res->mainWindow = SDL_CreateWindow("Tic-Tac-Toe", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			400,                               // width, in pixels
			450,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (res->mainWindow == NULL ) {
		spMainWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->mainRenderer = SDL_CreateRenderer(res->mainWindow, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->mainRenderer == NULL ) {
		// In the case that the window could not be made...
		spMainWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	loadingSurface = SDL_LoadBMP("./graphics/images/start.bmp");
	if (loadingSurface == NULL ) {
		spMainWindowDestroy(res);
		printf("couldn't create start.bmp surface\n");
		return NULL ;
	}
	res->startTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->startTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spMainWindowDestroy(res);
		printf("couldn't create start.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	loadingSurface = SDL_LoadBMP("./graphics/images/exit.bmp");
	if (loadingSurface == NULL ) {
		spMainWindowDestroy(res);
		printf("couldn't create exit.bmp surface\n");
		return NULL ;
	}
	res->exitTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->exitTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spMainWindowDestroy(res);
		printf("couldn't create exit.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	return res;
}

void spMainWindowDestroy(SPMainWin* src) {
	if (!src) {
		return;
	}
	if (src->startTexture != NULL ) {
		SDL_DestroyTexture(src->startTexture);
	}
	if (src->exitTexture != NULL ) {
		SDL_DestroyTexture(src->exitTexture);
	}
	if (src->mainRenderer != NULL ) {
		SDL_DestroyRenderer(src->mainRenderer);
	}
	if (src->mainWindow != NULL ) {
		SDL_DestroyWindow(src->mainWindow);
	}
	free(src);
}

void spMainWindowDraw(SPMainWin* src) {
	if(src==NULL){
		return;
	}
	SDL_Rect startR = { .x = 75, .y = 100, .h = 100, .w = 250 };
	SDL_Rect exitR = { .x = 75, .y = 250, .h = 100, .w = 250 };
	SDL_SetRenderDrawColor(src->mainRenderer, 255, 255, 255, 255);
	SDL_RenderClear(src->mainRenderer);
	SDL_RenderCopy(src->mainRenderer, src->startTexture, NULL, &startR);
	SDL_RenderCopy(src->mainRenderer, src->exitTexture, NULL, &exitR);
	SDL_RenderPresent(src->mainRenderer);
}

SP_MAIN_EVENT spMainWindowHandleEvent(SPMainWin* src, SDL_Event* event) {
	if (!event) {
		return SP_MAIN_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnStart(event->button.x, event->button.y)) {
			return SP_MAIN_START;
		} else if (isClickOnExit(event->button.x, event->button.y)) {
			return SP_MAIN_EXIT;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_MAIN_EXIT;
		}
		break;
	default:
		return SP_MAIN_NONE;
	}
	return SP_MAIN_NONE;
}

void spMainWindowHide(SPMainWin* src) {
	SDL_HideWindow(src->mainWindow);
}

void spMainWindowShow(SPMainWin* src) {
	SDL_ShowWindow(src->mainWindow);
}
