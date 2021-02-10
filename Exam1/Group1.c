/* Iain Moncrief */

/* TO COMPILE, ENTER:  gcc -Wall -ansi -o program Group1.c */

/* TO RUN, ENTER PROGRAM ARGUMENTS: SIZE  */
/* FOR EXAMPLE:  ./program 10   */


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<assert.h>

#define TYPE int
#define LT(a, b) (a<b)
#define GT(a, b) (a>b)
#define EQ(a, b) (a == b)

struct DynArr {
   TYPE * data;
   int size;
   int capacity;
};

/*----------------------------------------------*/
/*Interface for Sorted Bag*/
void initSortedBag(struct DynArr * bag, int capacity);
void addSortedBag(struct DynArr * bag, TYPE val);
void removeSortedBag(struct DynArr * bag, TYPE val);


/*----------------------------------------------*/
/*Auxiliary functions*/
void _increaseCapacity (struct DynArr * bag);
void _printBag(struct DynArr * bag);

void sort(TYPE* number, int n);
void swap(TYPE* x, TYPE* y);

/*----------------------------------------------*/
int main(int argc, char **argv){
   struct DynArr sorted;
   int i;
   int  capacity = 1;
   int  size = atoi(argv[1]);

   if(size < 0){
     printf("\nInvalid value for the size of Bag; size must be a positive integer.\n");
     return 0;
   }

   initSortedBag(&sorted, capacity);


   /*Generate integers in [0,100] and add them
     to the sorted bag in the ascending order*/
   srand ( time(NULL) );
   for(i=0; i<size; i++) addSortedBag(&sorted, rand()%101);

   printf("\nSorted bag after adding %d elements:\n", size);
   _printBag(&sorted);

   addSortedBag(&sorted, 200);

   printf("\nSorted bag after adding %d:\n", 200);
   _printBag(&sorted);

   addSortedBag(&sorted, -1);

   printf("\nSorted bag after adding %d:\n", -1);
   _printBag(&sorted);

   TYPE val = sorted.data[1];

   removeSortedBag(&sorted, val);

   printf("\nSorted bag after removing %d:\n", val);
   _printBag(&sorted);

   removeSortedBag(&sorted, 200);

   printf("\nSorted bag after removing %d:\n", 200);
   _printBag(&sorted);

   removeSortedBag(&sorted, -1);

   printf("\nSorted bag after removing %d:\n", -1);
   _printBag(&sorted);

   removeSortedBag(&sorted, 500);

   printf("\nSorted bag after attempting to remove %d:\n", 500);
   _printBag(&sorted);


   return 0;
}

/*----------------------------------------------*/
/* Initializes a sorted bag
  input arguments:
  bag -- pointer to a bag implemented as a dynamic array
  cap -- capacity of memory block allocated to dynamic array
*/
void initSortedBag(struct DynArr * bag, int cap) {
   assert (bag!=0 && cap>0);
   /* FIX ME */
   bag->data = (TYPE*)malloc(sizeof(TYPE) * cap);
   bag->capacity = cap;
   bag->size = 0;
}


/*----------------------------------------------*/
/* Increases the memory capacity of a sorted bag */
/*  Input: bag -- pointer to a bag implemented as a dynamic array */
void _increaseCapacity (struct DynArr * bag) {
  assert (bag);
   /* FIX ME */
   TYPE* old_data;
   old_data = bag->data;
   int new_cap;
   new_cap = (bag->capacity + 1) * 2;
   bag->data = (TYPE*)malloc(sizeof(TYPE) * new_cap);
   assert(bag->data != NULL);
   int i;
   i = 0;
   while (i < bag->size) {
      bag->data[i] = old_data[i];
      ++i;
   }
   bag->capacity = new_cap;
   free(old_data);
}

/*----------------------------------------------*/
/* Prints out all elements of a sorted bag */
/*  Input: bag -- pointer to a bag implemented as a dynamic array */
void _printBag(struct DynArr * bag) {
   assert (bag);
   int i;
   if(bag->size == 0) printf("Sorted dynamic array is empty!\n");
   for(i=0; i< bag->size; i++) printf("%d, ", bag->data[i]);
   printf("\n");
}

/*----------------------------------------------*/
/* Adds a new element to a bag sorted in the ascending order
  input arguments:
  bag -- pointer to a bag implemented as a dynamic array 
  val -- value of the data element to be added
  After returning from the function the bag must remain sorted
*/
void addSortedBag(struct DynArr * bag, TYPE val) {
   assert(bag);
   /* FIX ME */
   if (bag->size >= bag->capacity) {
      _increaseCapacity(bag);
   }
   bag->data[bag->size] = val;
   bag->size++;
   sort(bag->data, bag->size);
}

/*----------------------------------------------*/
/* Removes a single element from a bag sorted in the ascending order
  input arguments:
  bag -- pointer to a bag implemented as a dynamic array
  val -- value of the data element to be removed
  After returning from the function the bag must remain sorted
*/
void removeSortedBag(struct DynArr * bag, TYPE val) {
   assert(bag);
   /* FIX ME */
   int i;
   i = 0;
   while (i < bag->size) {
      if (EQ(bag->data[i], val)) {
         bag->data[i] = bag->data[bag->size - 1];
         bag->size--;
         break;
      }
      ++i;
   }
   sort(bag->data, bag->size);
}

void swap(TYPE* x, TYPE* y) {
    TYPE temp = *x;
    *x = *y;
    *y = temp;
}

void sort(TYPE* number, int n){
   assert(number != NULL);    
    /* Bubble sort implementation */
    int i, j, swapped;
    for (i = 0; i < n-1; i += 1) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j += 1) {
            if (GT(number[j], number[j+1])) {
                swap(&number[j], &number[j+1]);
                swapped = 1;
            }
        }
        if (swapped < 1) {
            break;
        }
    }
}