/*
 * GUI_base.c
 *
 *  Created on: Sep 13, 2017
 *      Author: liron
 */
#include "GUI_base.h"

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
