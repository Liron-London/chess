/*
 * minimax_unit_test.c
 *
 *  Created on: Sep 4, 2017
 *      Author: Gal
 */

#include "minimax.h"


int main() {
	printf("start checking...\n");
	bool success = game_create_test();
	if(success) {
		printf("Game create success\n");
	}
}


