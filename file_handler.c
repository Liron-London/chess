/*
 * file_handler.c
 *
 *  Created on: Aug 12, 2017
 *      Author: lironl
 */
# include "file_handler.h"

int save_game(game* cur_game, char* filename) {
	FILE* fp = fopen("filename", "w");
	if (fp == NULL) {
		return 1;
	}
	fprintf(fp, "<game>\n");
	fprintf(fp, "\t<current_turn>%d</current_turn>\n", cur_game->current_turn);
	fprintf(fp, "\t<game_mode>%d</game_mode>\n", cur_game->game_mode);
	fprintf(fp, "\t<difficulty>%d</difficulty>\n", cur_game->difficulty);
	fprintf(fp, "\t<user_color>%d</user_color>\n", cur_game->user_color);
	fprintf(fp, "\t<board>\n");
	// print the board
	for (int i= 0; i < 8; i++) {
		fprintf(fp, "\t\t<row_%d>", i);
		for (int j = 0; j < 8; j++) {
			if (cur_game->board[i][j] == EMPTY_ENTRY) {
				fprintf(fp, "_");
			} else {
				fprintf(fp, "%c", cur_game->board[i][j]);
			}
		}
		fprintf(fp, "\t\t<row_%d>", i);
	}
	//
	fprintf(fp, "\t</board>\n");
	fprintf(fp, "</game>\n");
	return 0;
}

int load_game(game* cur_game, char* filename) {
	FILE* fp = fopen("filename", "r");
	if (fp == NULL) {
		return 1;
	}

}

