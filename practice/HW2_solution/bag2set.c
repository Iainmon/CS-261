/* bag2set.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynArray.h"


/* Converts the input bag into a set using dynamic arrays 
	param: 	da -- pointer to a bag 	
	return value: void
        result: after exiting the function da points to a set 		
*/
void bag2set(struct DynArr *da){
    int i;
    TYPE temp;
    struct DynArr *auxBag;  /* auxiliary bag */

    /* initialize auxBag  (2pt) */
    auxBag =  (struct DynArr *) malloc(sizeof(struct DynArr));
    initDynArr(auxBag, da->capacity);     /*1pt*/

     /* iterate over elements of the input bag  (2pt)*/
     for(i = 0; i < da->size; i++){
         /* get an element from the bag  (2pt) */
         temp = da->data[i];
         /* copy this element to auxBag if unique (4pts) */
         if (containsDynArr(auxBag, temp) == -1)    /*2pt*/
            addDynArr(auxBag, temp); /*2pt*/
}
     /* the original bag is not needed anymore (4pts) */
     free(da->data);  /*2pt*/
     da->data = auxBag->data; /*1pt*/
     da->size = auxBag->size; /*1pt*/
}

int main(int argc, char* argv[]){

	int i;
        struct DynArr da;  /* bag */
        
        initDynArr(&da, 100);
        da.size = 10;
        	da.data[0] = 1.3;
	for (i=1;i<da.size;i++){
	    da.data[i] = 1.2;
	 }
    
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
        
	return 0;	
}

