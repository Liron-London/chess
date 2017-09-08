/*
 * GUI.c
 *
 *  Created on: Sep 8, 2017
 *      Author: lironl
 */

#include <SDL.h>
#include <SDL_video.h>

typedef struct window_t {
	void* data;
	void(*drawWindow)(window*);
};
