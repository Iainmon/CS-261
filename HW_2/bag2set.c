/* bag2set.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynArray.h"
#include <stdbool.h>

struct List {
    TYPE value;
    struct List* tail;
};

struct List* init() {
    return malloc(sizeof(struct List));
}
struct List* caboose(struct List* lis) {
    if (lis == NULL) return NULL;
    struct List* curr;
    curr = lis;
    while (curr->tail != NULL) {
        curr = curr->tail;
    }
    return curr;
}
struct List* append(struct List* lis, TYPE val) {
    struct List* next;
    next = init();
    next->value = val;
    if (lis == NULL) {
        lis = next;
    } else {
        struct List* back;
        back = caboose(lis);
        back->tail = next;
    }
    return lis;
}
bool has(struct List* lis, TYPE val) {
    struct List* curr;
    curr = lis;
    while (curr != NULL) {
        if (curr->value == val) {
            return true;
        }
        curr = curr->tail;
    }
    return false;
} 

/* Converts the input bag into a set using dynamic arrays 
	param: 	da -- pointer to a bag 	
	return value: void
        result: after exiting the function da points to a set 		
*/
void bag2set(struct DynArr *da)
{
    
    struct List* uniques;
    uniques = NULL;
    int count; count = 0;
    {
        TYPE curr;
        int i; i = 0;
        while (i < da->size) {
            curr = getDynArr(da, i);
            if (!has(uniques, curr)) {
                uniques = append(uniques, curr);
                ++count;
            }
            ++i;
        }
    }

    freeDynArr(da);
    _dynArrSetCapacity(da, count);

    {
        struct List* curr;
        curr = uniques;
        while (curr != NULL) {
            addDynArr(da, curr->value);
            curr = curr->tail;
        }
    }

}



/* An example how to test your bag2set() */
int main(int argc, char* argv[]){

	int i;
        struct DynArr da;  /* bag */
        
        initDynArr(&da, 100);
        da.size = 11;
        da.data[0] = 1.3;
	for (i=1;i<da.size-1;i++){
	    da.data[i] = 1.2;
	 }
        da.data[da.size-1] = 1.4;

        printf("Bag:\n\n");
	for (i=0;i<da.size;i++){
          printf("%g  \n", da.data[i]);
        }
        
        printf("\n\n\n");
        printf("Set:\n\n");
        bag2set(&da);
	for (i=0;i<da.size;i++){
          printf("%g ", da.data[i]);
        }
        printf("\n");
    
    freeDynArr(&da);
        
	return 0;	
}

