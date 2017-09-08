#ifndef SPTICTACTOEGUIMANAGER_H_
#define SPTICTACTOEGUIMANAGER_H_
#include <SDL.h>
#include "SPTicTacToeGameWin.h"
#include "SPTicTacToeMainWin.h"

typedef enum{
	SP_MAIN_WINDOW_ACTIVE,
	SP_GAME_WINDOW_ACTIVE
}ACTIVE_WINDOW;

typedef enum{
	SP_MANAGER_QUTT,
	SP_MANAGER_NONE,
}SP_MANAGER_EVENET;

typedef struct {
	SPGameWin* gameWin;
	SPMainWin* mainWin;
	ACTIVE_WINDOW activeWin;
} SPGuiManager;

SPGuiManager* spManagerCreate();

void spManagerDestroy(SPGuiManager* src);

void spManagerDraw(SPGuiManager* src);

SP_MANAGER_EVENET spManagerHandleEvent(SPGuiManager* src, SDL_Event* event) ;


#endif
