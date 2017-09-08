#include "SPTicTacToeGUIManager.h"
#include <stdio.h>
#include <stdlib.h>

SPGuiManager* spManagerCreate() {
	SPGuiManager* res = (SPGuiManager*) malloc(sizeof(SPGuiManager));
	if (res == NULL ) {
		return NULL ;
	}
	res->mainWin = spMainWindowCreate();
	if (res->mainWin == NULL ) {
		free(res);
		return NULL ;
	}
	res->gameWin = NULL;
	res->activeWin = SP_MAIN_WINDOW_ACTIVE;
	return res;
}
void spManagerDestroy(SPGuiManager* src) {
	if (!src) {
		return;
	}
	if (src->activeWin == SP_GAME_WINDOW_ACTIVE) {
		spGameWindowDestroy(src->gameWin);
	}
	spMainWindowDestroy(src->mainWin);
	free(src);
}
void spManagerDraw(SPGuiManager* src) {
	if (!src) {
		return;
	}
	if (src->activeWin == SP_MAIN_WINDOW_ACTIVE) {
		spMainWindowDraw(src->mainWin);
	} else {
		spGameWindowDraw(src->gameWin);
	}
}
SP_MANAGER_EVENET handleManagerDueToMainEvent(SPGuiManager* src,
		SP_MAIN_EVENT event) {
	if (src == NULL ) {
		return SP_MANAGER_NONE;
	}
	if (event == SP_MAIN_START) {
		spMainWindowHide(src->mainWin);
		src->gameWin = spGameWindowCreate();
		if (src->gameWin == NULL ) {
			printf("Couldn't create game window\n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_GAME_WINDOW_ACTIVE;
	}
	if (event == SP_MAIN_EXIT) {
		return SP_MANAGER_QUTT;
	}
	return SP_MANAGER_NONE;
}

SP_MANAGER_EVENET handleManagerDueToGameEvent(SPGuiManager* src,
		SP_GAME_EVENT event) {
	if (event == SP_GAME_EVENT_NONE || src == NULL ) {
		return SP_MANAGER_NONE;
	}
	if (event == SP_GAME_EVENT_X_WON) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "X won",
				NULL );
	} else if (event == SP_GAME_EVENT_O_WON) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "O won",
				NULL );
	} else if (event == SP_GAME_EVENT_TIE) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over",
				"it's a tie", NULL );
	}
	spGameWindowDestroy(src->gameWin);
	src->gameWin = NULL;
	src->activeWin = SP_MAIN_WINDOW_ACTIVE;
	spMainWindowShow(src->mainWin);
	return SP_MANAGER_NONE;
}

SP_MANAGER_EVENET spManagerHandleEvent(SPGuiManager* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
		return SP_MANAGER_NONE;
	}
	if (src->activeWin == SP_MAIN_WINDOW_ACTIVE) {
		SP_MAIN_EVENT mainEvent = spMainWindowHandleEvent(src->mainWin, event);
		return handleManagerDueToMainEvent(src, mainEvent);
	} else {
		SP_GAME_EVENT gameEvent = spGameWindowHandleEvent(src->gameWin, event);
		spManagerDraw(src);
		return handleManagerDueToGameEvent(src, gameEvent);
	}
	return SP_MANAGER_NONE;
}
