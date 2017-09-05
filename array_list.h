#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#include <stdbool.h>
#include <stdlib.h>
#include "moves.h"

/**
 * ArrayList summary:
 *
 * A container that represents a fixed size linked list. The capcity of the list
 * is specified at the creation. The container supports typical list
 * functionalities with the addition of random access as in arrays.
 * Upon insertion, if the maximum capacity is reached then an error message is
 * returned and the list is not affected. A summary of the supported functions
 * is given below:
 *
 * spArrayListCreate       - Creates an empty array list with a specified
 *                           max capacity.
 * spArrayListCopy         - Creates an exact copy of a specified array list.
 * spArrayListDestroy      - Frees all memory resources associated with an array
 *                           list.
 * spArrayListClear        - Clears all elements from a specified array list.
 * spArrayListAddAt        - Inserts an element at a specified index, elements
 *                           will be shifted to make place.
 * spArrayListAddFirst     - Inserts an element at the beginning of the array
 *                           list, elements will be shifted to make place.
 * spArrayListAddLast      - Inserts an element at the end of the array list.
 * spArrayListRemoveAt     - Removes an element at the specified index, elements
 *                           elements will be shifted as a result.
 * spArrayListRemoveFirst  - Removes an element from the beginning of the array
 *                           list, elements will be shifted as a result.
 * spArrayListRemoveLast   - Removes an element from the end of the array list
 * spArrayListGetAt        - Accesses the element at the specified index.
 * spArrayListGetFirst     - Accesses the first element of the array list.
 * spArrayListGetLast      - Accesses the last element of the array list.
 * spArrayListMaxCapcity   - Returns the maximum capcity of the array list.
 * spArrayListSize         - Returns the number of elements in that array list.
 * spArrayListIsFull       - Returns if the array list reached its max capacity.
 * spArrayListIsEmpty      - Returns true if the array list contains no elements.
 */
typedef struct array_list_t {
	game** previous_games;
	move** previous_moves;
	int actualSize;
	int maxSize;
} array_list;

/**
 * A type used for errors
 */
typedef enum array_list_message_t {
	ARRAY_LIST_SUCCESS,
	ARRAY_LIST_INVALID_ARGUMENT,
	ARRAY_LIST_FULL,
	ARRAY_LIST_EMPTY
} ARRAY_LIST_MESSAGE;

ARRAY_LIST_MESSAGE array_list_add_at(array_list* src, game* game, move* move, int index);

array_list* array_list_create(int maxSize);

array_list* array_list_copy(array_list* src) ;

void array_list_destroy(array_list* src) ;

ARRAY_LIST_MESSAGE array_list_add_at(array_list* src, game* game, move* move, int index);

ARRAY_LIST_MESSAGE array_list_add_first(array_list* src, game* game, move* move) ;

ARRAY_LIST_MESSAGE array_list_add_last(array_list* src, game* game, move* move);

ARRAY_LIST_MESSAGE array_list_remove_at(array_list* src, int index);

ARRAY_LIST_MESSAGE array_list_remove_first(array_list* src);

ARRAY_LIST_MESSAGE array_list_remove_last(array_list* src);

game* array_list_get_game_at(array_list* src, int index);

move* array_list_get_move_at(array_list* src, int index);

game* array_list_get_first_game(array_list* src);

move* array_list_get_first_move(array_list* src);

game* array_list_get_last_game(array_list* src);

move* array_list_get_last_move(array_list* src);

int array_list_max_capacity(array_list* src);

int array_list_size(array_list* src);

bool array_list_is_full(array_list* src);

bool array_list_is_empty(array_list* src);

#endif
