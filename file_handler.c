/*
 * file_handler.c
 *
 *  Created on: Aug 12, 2017
 *      Author: lironl
 */
# include "file_handler.h"
#include "debug.h"
#include <string.h>

/*
 * get a game and uses its board to update all pieces status
 */
void update_pieces_for_load(game* cur_game){
	// kill all pieces
	for (int i=0; i<16;i++){
		cur_game->whites[i]->alive = 0;
		cur_game->blacks[i]->alive = 0;
	}

	int pawn_index = 8;
	bool first_piece;
	// UPDATE WHITES //

	char white_pieces[] = {'r', 'n', 'b', 'q', 'k'};
	for (int i=0; i<5; i++){
		first_piece = true;
		for (int j=0; j<8;j++){
			for (int k=0; k<8; k++){
				if (cur_game->board[j][k] == white_pieces[i]){
					if (first_piece){
						cur_game->whites[i]->piece_type = cur_game->board[j][k];
						cur_game->whites[i]->alive = 1;
						cur_game->whites[i]->piece_location->row = j;
						cur_game->whites[i]->piece_location->column = k;
						first_piece = false;
					}
					else{
						cur_game->whites[7-i]->piece_type = cur_game->board[j][k];
						cur_game->whites[7-i]->alive = 1;
						cur_game->whites[7-i]->piece_location->row = j;
						cur_game->whites[7-i]->piece_location->column = k;
					}
				}
			}
		}
	}

	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			if (cur_game->board[i][j] == 'm'){
				cur_game->whites[pawn_index]->piece_type = 'm';
				cur_game->whites[pawn_index]->alive = 1;
				cur_game->whites[pawn_index]->piece_location->row = i;
				cur_game->whites[pawn_index]->piece_location->column = j;
				pawn_index += 1;
			}
		}
	}

	// update blacks
	pawn_index = 8;

	char black_pieces[] = {'R', 'N', 'B', 'Q', 'K'};
	for (int i=0; i<5; i++){
		first_piece = true;
		for (int j=0; j<8;j++){
			for (int k=0; k<8; k++){
				if (cur_game->board[j][k] == black_pieces[i]){
					if (first_piece){
						cur_game->blacks[i]->piece_type = cur_game->board[j][k];
						cur_game->blacks[i]->alive = 1;
						cur_game->blacks[i]->piece_location->row = j;
						cur_game->blacks[i]->piece_location->column = k;
						first_piece = false;
					}
					else{
						cur_game->blacks[7-i]->piece_type = cur_game->board[j][k];
						cur_game->blacks[7-i]->alive = 1;
						cur_game->blacks[7-i]->piece_location->row = j;
						cur_game->blacks[7-i]->piece_location->column = k;
					}
				}
			}
		}
	}

	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			if (cur_game->board[i][j] == 'M'){
				cur_game->blacks[pawn_index]->piece_type = 'M';
				cur_game->blacks[pawn_index]->alive = 1;
				cur_game->blacks[pawn_index]->piece_location->row = i;
				cur_game->blacks[pawn_index]->piece_location->column = j;
				pawn_index += 1;
			}
		}
	}
}
/*
 * save game object to a file - no extension is added!
 */
int save_game(game* cur_game, char* filename) {
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("File cannot be created or modified\n");
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

/*
 * finds the string in a tag in a save game
 */
char* tag_finder(char* input_file_text, char* tag) {
//	int tag_len = strlen(tag);
	char open_tag[30], close_tag[30];

	sprintf(open_tag, "<%s>", tag);
	sprintf(close_tag, "</%s>", tag);

	char* content_start = strstr(input_file_text, ">");
	char* content_end = strstr(input_file_text, "</");

	int len = (int)(content_end - content_start) - 1;

	char* content = malloc((len + 1)* sizeof(char));
	strncpy(content, content_start+1, len);
	content[len] = '\0';
	return content;
}

int load_game(game* cur_game, char* filename) {
	//strcat(filename, ".xml");
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error: File doesn't exist or cannot be opened\n");
		return 1;
	}
	char input_file_text[50];
	char* tag_content;

	fgets(input_file_text, 50, fp); // gets the formatting line
	fgets(input_file_text, 50, fp); // gets the <game> line
	fgets(input_file_text, 50, fp); // gets the <current_turn> line
	tag_content = tag_finder(input_file_text, "current_turn");
	cur_game->current_turn = atoi(tag_content);

	fgets(input_file_text, 50, fp); // gets the <game_mode> line
	tag_content = tag_finder(input_file_text, "game_mode");
	cur_game->game_mode = atoi(tag_content);

	fgets(input_file_text, 50, fp); // gets the <difficulty> line
	tag_content = tag_finder(input_file_text, "difficulty");
	cur_game->difficulty = atoi(tag_content);

	fgets(input_file_text, 50, fp); // gets the <user_color> line
	tag_content = tag_finder(input_file_text, "user_color");
	cur_game->user_color = atoi(tag_content);

	fgets(input_file_text, 50, fp); // gets the <board> line

	// fill board
	for (int i = 8; i >= 1; i--) {
	fgets(input_file_text, 50, fp); // gets the <row_i> line
		char row_x[5];
		sprintf(row_x, "row_%d", i);
		tag_content = tag_finder(input_file_text, row_x);
		for (int j = 0; j <= 7; j++) {
			cur_game->board[i-1][j] = tag_content[j];
		}
	}
	update_pieces_for_load(cur_game);

//	if((cur_game->game_mode == 1 && cur_game->user_color == 0)) {
//		print_board(cur_game);
//	}
	// game_play(cur_game);
	return 0;
}

void generate_filename(int index, char* filename) {
	sprintf(filename, "chess_game_%c", index + '0');
}

/*
 * save the new game to chess_game_0 and shift all the others
 */
void default_save(game* game, int num_games){
	save_game(game, "tmp_game");
	char filename[13];

	for (int i=num_games; i > 0 ;i--){
		generate_filename(i, filename);
		load_game(game, filename);
		if (num_games < 5){
			generate_filename(i+1, filename);
			save_game(game, filename);
		}
	}

	load_game(game, "tmp_game");
	generate_filename(1, filename);
	save_game(game, filename);
}

int get_num_games(){
	int index = 0;
	for (int i=1; i<=5; i++){
		char filename[13]= "chess_game_";
		char idx[2] = {i + '0', '\0'};
		strcat(filename, idx);
		FILE* fp = fopen(filename, "r");
		if (fp == NULL){
			break;
		}
		index += 1;
	}
	return index;
}
