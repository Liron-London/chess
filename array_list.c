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
    array->elements = calloc(maxSize, sizeof(int));
    if (array->elements == NULL) {
        free(array);
        return NULL;
    }
    return array;
}

array_list* array_list_copy(array_list* src) {
    if (src == NULL) {
        return NULL;
    }
    array_list* copied_array = malloc(sizeof(array_list));
    if (copied_array == NULL) {
        return NULL;
    }
    copied_array->maxSize = src->maxSize;
    copied_array->elements = calloc(copied_array->maxSize, sizeof(int));
    copied_array->actualSize = 0;
    if (copied_array->elements == NULL) {
        free(copied_array);
        return NULL;
    }
    for (int i = 0; i < src->actualSize; i++) {
        array_list_add_last(copied_array, src->elements[i]);
    }
    return copied_array;

}

void array_list_destroy(array_list* src) {
    if (src != NULL){
        free(src->elements);
        free(src);
    }
}

ARRAY_LIST_MESSAGE array_list_clear(array_list* src) {
    if (src == NULL) {
        return ARRAY_LIST_INVALID_ARGUMENT;
    }
    for (int i = 0; i < src->actualSize; i++) {
        src->elements[i] = 0;
    }
    src->actualSize = 0;
    return ARRAY_LIST_SUCCESS;
}


ARRAY_LIST_MESSAGE array_list_add_at(array_list* src, int elem, int index) {
    if (src == NULL || index < 0 || index > src->actualSize+1) {
        return ARRAY_LIST_INVALID_ARGUMENT;
    }
    if (src->actualSize == src->maxSize) {
        return ARRAY_LIST_FULL;
    }

    for (int i = src->actualSize; i > index; i--) {
        src->elements[i] = src->elements[i-1];
    }
    src->elements[index] = elem;
    src->actualSize++;
    return ARRAY_LIST_SUCCESS;
}

 ARRAY_LIST_MESSAGE array_list_add_first(array_list* src, int elem) {
     return(array_list_add_at(src, elem, 0));
 }


 ARRAY_LIST_MESSAGE array_list_add_last(array_list* src, int elem) {
     return(array_list_add_at(src, elem, src->actualSize));
 }


 ARRAY_LIST_MESSAGE array_list_remove_at(array_list* src, int index) {
        if (src == NULL || index < 0 || index > src->actualSize) {
            return ARRAY_LIST_INVALID_ARGUMENT;
        }

        for (int i = index; i < src->actualSize-1; i++) {
            src->elements[i] = src->elements[i+1];
        }
        src->actualSize--;
        return ARRAY_LIST_SUCCESS;
    }


 ARRAY_LIST_MESSAGE array_list_remove_first(array_list* src) {
     return array_list_remove_at(src, 0);
 }

 ARRAY_LIST_MESSAGE array_list_remove_last(array_list* src) {
     return array_list_remove_at(src, src->actualSize-1);
 }


 int array_list_get_at(array_list* src, int index) {
     if (src == NULL || index < 0 || index > src->actualSize) {
                return -1;
            }
     else {
         return src->elements[index];
     }
 }

 int array_list_get_first(array_list* src) {
     return array_list_get_at(src, 0);
 }

 int array_list_get_last(array_list* src) {
     return array_list_get_at(src, src->actualSize-1);
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
