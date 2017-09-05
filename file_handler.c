/*
 * file_handler.c
 *
 *  Created on: Aug 12, 2017
 *      Author: lironl
 */
# include "file_handler.h"
#include "debug.h"

int save_game(game* cur_game, char* filename) {
	strcat(filename, ".xml");
	DEBUG("filename is: %s\n", filename);
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		return 1;
	}
	fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(fp, "<game>\n");
	fprintf(fp, "\t<current_turn>%d</current_turn>\n", cur_game->current_turn);
	fprintf(fp, "\t<game_mode>%d</game_mode>\n", cur_game->game_mode);
	fprintf(fp, "\t<difficulty>%d</difficulty>\n", cur_game->difficulty);
	fprintf(fp, "\t<user_color>%d</user_color>\n", cur_game->user_color);
	fprintf(fp, "\t<board>\n");
	// print the board
	for (int i=7; i >= 0; i--) {
		fprintf(fp, "\t\t<row_%d>", i+1);
		for (int j = 0; j < 8; j++) {
			if (cur_game->board[i][j] == EMPTY_ENTRY) {
				fprintf(fp, "_");
			} else {
				fprintf(fp, "%c", cur_game->board[i][j]);
			}
		}
		fprintf(fp, "</row_%d>\n", i+1);
	}

	fprintf(fp, "\t</board>\n");
	fprintf(fp, "</game>\n");
	fclose(fp);
	return 0;
}

void tag_finder(char* input_file_text, char* tag, char* content) {
	int tag_len = strlen(tag);
	char open_tag[30], close_tag[30];

	sprintf(open_tag, "<%s>", tag);
	sprintf(close_tag, "</%s>", tag);

	char* content_start = strstr(input_file_text, open_tag) + 2 + tag_len;
	char* content_end = strstr(input_file_text, close_tag);

	strncpy(content, content_start, content_end - content_start);
}

int load_game(game* cur_game, char* filename) {
	DEBUG("in load_game, filename is: %s\n", filename);
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		return 1;
	}
	char input_file_text[1024];
	fscanf(fp, "%s", input_file_text);
	char tag_content[8];

	tag_finder(input_file_text, "current_turn", tag_content);
	cur_game->current_turn = atoi(tag_content);

	tag_finder(input_file_text, "game_mode", tag_content);
	cur_game->game_mode = atoi(tag_content);

	tag_finder(input_file_text, "difficulty", tag_content);
	cur_game->difficulty = atoi(tag_content);

	tag_finder(input_file_text, "user_color", tag_content);
	cur_game->user_color = atoi(tag_content);

	for (int i = 8; i >= 1; i--) {
		char row_x[5];
		sprintf(row_x, "row_%d", i);
		tag_finder(input_file_text, row_x, tag_content);
		for (int j = 0; j <= 7; j++) {
			cur_game->board[i][j] = tag_content[j];
		}
	}

	printf("Difficulty is: %d\n", cur_game->difficulty);
	game_play(cur_game);
	return 0;
}

