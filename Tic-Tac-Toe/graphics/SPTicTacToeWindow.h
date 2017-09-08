#ifndef SPTICTACTOEWINDOW_H_
#define SPTICTACTOEWINDOW_H_
#include <SDL.h>
#include <SDL_video.h>
/*
typedef enum {
//Add messages here
} SP_EVENT_MSG;
*/
typedef struct sp_tic_tac_toe_window_t SPTicTacToeWin;

struct sp_tic_tac_toe_window_t {
	SDL_Window* window;
	SDL_Renderer* renderer;
	void (*destroyWindowFunc)(SPTicTacToeWin*);
	void (*drawFunc)(SPTicTacToeWin*);
	//SP_EVENT_MSG (*handleEventFunc)(SPTicTacToe*, SDL_Event*);
};

#endif
