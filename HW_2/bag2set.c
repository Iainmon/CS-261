/* bag2set.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynArray.h"
#include <assert.h>


/* Converts the input bag into a set using dynamic arrays 
	param: 	da -- pointer to a bag 	
	return value: void
        result: after exiting the function da points to a set 		
*/
void bag2set(struct DynArr *da) {
    assert(da != NULL);
    if (da->size < 1) return;
    struct DynArr *uniques;
    uniques = newDynArr(da->size);
    int i;
    i = 0;
    while (i < da->size) {
        if (containsDynArr(uniques, da->data[i]) == -1) {
            addDynArr(uniques, da->data[i]);
        }
        ++i;
    }
    free(da->data);
    *da = *uniques;
    uniques->data = NULL;
    deleteDynArr(uniques);
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
<<<<<<< HEAD
        
	return 0;	
=======
	
    return 0;	
>>>>>>> a3a85416f4090a5cc361e57dbcb9c00cc0abe630
}

