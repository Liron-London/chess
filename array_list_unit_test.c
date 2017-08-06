/*
 * array_list_unit_test.c
 *
 *  Created on: 6 August 2017
 *      Author: lironlondon
 */
#include "array_list_unit_test.h"

static bool array_list_create_test() {
	array_list* list = array_list_create(CAPACITY_SIZE);
	if (list == NULL) {
		spArrayListDestroy(list);
	}
	if (list->actualSize != 0 ) {
		printf("List size is %d, when it should be 0\n", list->actualSize);
		return false;
	}
	if (list->maxSize != CAPACITY_SIZE) {
		printf("List maxSize is %d, when it should be %d\n", list->maxSize, CAPACITY_SIZE);
		return false;
	}
	if (list->elements[CAPACITY_SIZE - 1] != 0 ) {
		printf("Error initializing list elements\n");
		return false;
	}
	array_list_destroy(list);
	return true;
}

static bool array_list_add_test() {
	array_list* list = array_list_create(CAPACITY_SIZE);
	if (list == NULL) {
		spArrayListDestroy(list);
	}
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		array_list_add_at(list, i, i);
	}
	for (int j = 0; j < CAPACITY_SIZE; j++) {
		if (array_list_get_at(list, j) != j) {
			printf("Error adding elements to list or getting them from list\n");
			return false;
		}
	}
	array_list_add_first(list, 100);
	array_list_add_last(list, 500);
	if (array_list_get_at(list, 0) != 100) {
		printf("Error adding first element to list or getting it\n");
		return false;
	}
	if (array_list_get_at(list, CAPACITY_SIZE - 1) != 500) {
		printf("Error adding last element to list or getting it\n");
		return false;
	}
	array_list_destroy(list);
	return true;
}

static bool array_list_copy_test() {
	array_list* list = array_list_create(CAPACITY_SIZE);
	if (list == NULL) {
		array_list_destroy(list);
	}
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		array_list_add_at(list, i, i);
	}
	array_list* list_copy = array_list_copy(list);
	for (int j = 0; j < CAPACITY_SIZE; j++) {
		if (array_list_get_at(list_copy, j) != j) {
			printf("Error copying list\n");
			return false;
		}
	}
	array_list_destroy(list_copy);
	array_list_destroy(list);
	return true;
}

static bool array_list_remove_test() {
	array_list* list = array_list_create(CAPACITY_SIZE);
	if (list == NULL) {
		spArrayListDestroy(list);
	}
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		array_list_add_at(list, i, i);
	}
	// test remove_first
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		array_list_remove_first(list);
	}
	if (list->actualSize != 0) {
		printf("Error removing first element from list\n");
		return false;
	}
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		array_list_add_at(list, i, i);
	}
	// test remove_last
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		array_list_remove_last(list);
	}
	if (list->actualSize != 0) {
		printf("Error removing last element from list\n");
		return false;
	}
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		array_list_add_at(list, i, i);
	}
	// test remove_last
	for (int i = CAPACITY_SIZE; i < 0; i--) {
		array_list_remove_at(list, i);
	}
	if (list->actualSize != 0) {
		printf("Error removing last element from list\n");
		return false;
	}

	array_list_destroy(list);
	return true;
}

int main() {
	bool success;
	success = array_list_create_test();
	success = array_list_add_test();
	success = array_list_copy_test();
	success = array_list_remove_test();
	if (!success) {
		printf("Undetected error\n");
	}
	return 0;
}

