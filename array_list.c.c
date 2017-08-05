#include "SPArrayList.h"
#include <stdio.h>
#include <stdlib.h>

SPArrayList* spArrayListCreate(int maxSize) {
    if (maxSize <=0) {
        return NULL;
    }

    SPArrayList *array = malloc(sizeof(SPArrayList));
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

SPArrayList* spArrayListCopy(SPArrayList* src) {
    if (src == NULL) {
        return NULL;
    }
    SPArrayList* copied_array = malloc(sizeof(SPArrayList));
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
        spArrayListAddLast(copied_array, src->elements[i]);
    }
    return copied_array;

}

void spArrayListDestroy(SPArrayList* src) {
    if (src != NULL){
        free(src->elements);
        free(src);
    }
}

SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src) {
    if (src == NULL) {
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }
    for (int i = 0; i < src->actualSize; i++) {
        src->elements[i] = 0;
    }
    src->actualSize = 0;
    return SP_ARRAY_LIST_SUCCESS;
}


SP_ARRAY_LIST_MESSAGE spArrayListAddAt(SPArrayList* src, int elem, int index) {
    if (src == NULL || index < 0 || index > src->actualSize+1) {
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }
    if (src->actualSize == src->maxSize) {
        return SP_ARRAY_LIST_FULL;
    }

    //for is wrong, check what happens when adding last and adding in the middle
    for (int i = src->actualSize; i >= index; i--) {
        src->elements[i+1] = src->elements[i];
    }
    src->elements[index] = elem;
    src->actualSize++;
    return SP_ARRAY_LIST_SUCCESS;
}

 SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, int elem) {
     return(spArrayListAddAt(src, elem, 0));
 }


 SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, int elem) {
     return(spArrayListAddAt(src, elem, src->actualSize+1));
 }


 SP_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPArrayList* src, int index) {
        if (src == NULL || index < 0 || index > src->actualSize) {
            return SP_ARRAY_LIST_INVALID_ARGUMENT;
        }

        for (int i = index; i <= src->actualSize; i++) {
            src->elements[i] = src->elements[i+1];
        }
        src->actualSize--;
        return SP_ARRAY_LIST_SUCCESS;
    }


 SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList* src) {
     return spArrayListRemoveAt(src, 0);
 }

 SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList* src) {
     return spArrayListRemoveAt(src, src->actualSize);
 }


 int spArrayListGetAt(SPArrayList* src, int index) {
     if (src == NULL || index < 0 || index > src->actualSize) {
                return -1;
            }
     else {
         return src->elements[index];
     }
 }

 int spArrayListGetFirst(SPArrayList* src) {
     return spArrayListGetAt(src, 0);
 }

 int spArrayListGetLast(SPArrayList* src) {
     return spArrayListGetAt(src, src->actualSize);
 }


 int spArrayListMaxCapacity(SPArrayList* src) {
     if (src == NULL){
         return -1;
     }
     return src->maxSize;
 }


 int spArrayListSize(SPArrayList* src) {
     if (src == NULL){
         return -1;
     }
     return src->actualSize;
 }


 bool spArrayListIsFull(SPArrayList* src) {
     if (src == NULL || src->actualSize < src->maxSize) {
         return false;
     }
     else {
         return true;
     }
 }

 bool spArrayListIsEmpty(SPArrayList* src) {
     if (src == NULL || src->actualSize > 0) {
         return false;
     }
     else {
         return true;
     }
 }
