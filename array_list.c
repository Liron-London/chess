#include "array_list.h"
#include "game_commands.h"
#include <stdio.h>
#include <stdlib.h>

array_list* array_list_create(int maxSize) {
	if (maxSize <=0) {
		return NULL;
	}

	array_list *array = malloc(sizeof(array_list));
	if (array == NULL) {
		return NULL;
	}
	array->actualSize = 0;
	array->maxSize = maxSize;
	array->previous_games = calloc(maxSize, sizeof(game*));
	if (array->previous_games == NULL) {
		free(array);
		return NULL;
	}

	array->previous_moves = calloc(maxSize, sizeof(move*));
	if (array->previous_moves == NULL) {
		free(array);
		return NULL;
	}

	return array;
}

array_list* array_list_copy(array_list* src) {
	if (src == NULL) {
		return NULL;
	}
	array_list* copied_array = array_list_create(src->maxSize);
	if (copied_array == NULL) {
		return NULL;
	}
	copied_array->actualSize = src->actualSize;
	for (int i=0; i<copied_array->actualSize; i++){
		copied_array->previous_games[i] = src->previous_games[i];
		copied_array->previous_moves[i] = src->previous_moves[i];
	}
	return copied_array;

}

void array_list_destroy(array_list* src) {
	if (src != NULL){
		for (int i=0; i<src->actualSize;i++){
			destroy_move(src->previous_moves[i]);
			game_destroy(src->previous_games[i]);
		}
		free(src->previous_games);
		free(src->previous_moves);
		free(src);
	}
}




ARRAY_LIST_MESSAGE array_list_add_at(array_list* src, game* game, move* move, int index) {
	if (src == NULL || index < 0 || index > src->actualSize+1) {
		return ARRAY_LIST_INVALID_ARGUMENT;
	}
	if (src->actualSize == src->maxSize) {
		return ARRAY_LIST_FULL;
	}

	for (int i = src->actualSize; i > index; i--) {
		src->previous_games[i] = src->previous_games[i-1];
		src->previous_moves[i] = src->previous_moves[i-1];
	}

	src->previous_games[index] = game;
	src->previous_moves[index] = move;

	src->actualSize++;
	return ARRAY_LIST_SUCCESS;
}

/*
 * add a game and a move to the head of the list
 */
 ARRAY_LIST_MESSAGE array_list_add_first(array_list* src, game* game, move* move) {
	 return(array_list_add_at(src, game, move, 0));
 }

 /*
  * add a game and a move to the top of the list
  */
 ARRAY_LIST_MESSAGE array_list_add_last(array_list* src, game* game, move* move) {
	 return array_list_add_at(src, game, move, src->actualSize);
 }

 /*
  * remove item from the list from a specific index
  */
 ARRAY_LIST_MESSAGE array_list_remove_at(array_list* src, int index) {
	 if (src == NULL || index < 0 || index > src->actualSize) {
		 return ARRAY_LIST_INVALID_ARGUMENT;
	 }
	 game_destroy(src->previous_games[index]);
	 destroy_move(src->previous_moves[index]);
	 for (int i = index; i < src->actualSize-1; i++) {
		 src->previous_games[i] = src->previous_games[i+1];
		 src->previous_moves[i] = src->previous_moves[i+1];
	 }
	 src->actualSize--;
	 return ARRAY_LIST_SUCCESS;
 }

 /*
  * remove the first element from the list
  */
 ARRAY_LIST_MESSAGE array_list_remove_first(array_list* src) {
	 return array_list_remove_at(src, 0);
 }

 /*
  * remove the last element of the list
  */
 ARRAY_LIST_MESSAGE array_list_remove_last(array_list* src) {
	 return array_list_remove_at(src, src->actualSize-1);
 }

 /*
  * get the game from a specific index of the list
  */
 game* array_list_get_game_at(array_list* src, int index) {
	 if (src == NULL || index < 0 || index > src->actualSize) {
		 return NULL;
	 }
	 else {
		 return src->previous_games[index];
	 }
 }
 /*
  * return a move from specific index
  */
 move* array_list_get_move_at(array_list* src, int index) {
	 if (src == NULL || index < 0 || index > src->actualSize) {
		 return NULL;
	 }
	 else {
		 return src->previous_moves[index];
	 }
 }

 /*
  * get the top game of the list
  */
 game* array_list_get_first_game(array_list* src) {
	 return array_list_get_game_at(src, 0);
 }
 /*
  * remove first game and move from the top of the list
  */
 move* array_list_get_first_move(array_list* src) {
	 return array_list_get_move_at(src, 0);
 }
 /*
  * get game in the bottom of the list
  */
 game* array_list_get_last_game(array_list* src) {
	 return array_list_get_game_at(src, src->actualSize-1);
 }
 /*
  * get the move in the bottom of the list
  */
 move* array_list_get_last_move(array_list* src) {
	 return array_list_get_move_at(src, src->actualSize-1);
 }

 int array_list_max_capacity(array_list* src) {
	 if (src == NULL){
		 return -1;
	 }
	 return src->maxSize;
 }

 int array_list_size(array_list* src) {
	 if (src == NULL){
		 return -1;
	 }
	 return src->actualSize;
 }

 bool array_list_is_full(array_list* src) {
	 if (src == NULL || src->actualSize < src->maxSize) {
		 return false;
	 }
	 else {
		 return true;
	 }
 }

 bool array_list_is_empty(array_list* src) {
	 if (src == NULL || src->actualSize > 0) {
		 return false;
	 }
	 else {
		 return true;
	 }
 }
