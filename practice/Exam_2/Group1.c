/* ENTER YOUR FIRST AND LAST NAME:      */

/* TO COMPILE:  gcc -Wall -ansi -o prog Group1.c */

/* TO RUN, ENTER SIZE OF BAG */
/* FOR EXAMPLE:  ./prog 10 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int
#define EQ(a,b) (a == b)


struct DLink {
   TYPE value;
   struct DLink * next;
   struct DLink * prev;
};


struct DList {
   int size;
   struct DLink * frontSentinel;
   struct DLink * backSentinel;
};

/*----------------------------------------------*/
/*Interface for doubly linked list*/
void initDList (struct DList *dl);
void freeDList (struct DList *dl);
void  _removeDLink (struct DList *dl, struct DLink *lnk);
void addFrontDList (struct DList *dl, TYPE val);
void addBackDList (struct DList *dl, TYPE val);
void _addDLink (struct DList *dl, struct DLink *lnk, TYPE val);
void _printDList(struct DList *dl);

/*----------------------------------------------*/
/*Interface for Bag implemented as doubly linked list*/
void removeAllBag(struct DList *bag, TYPE val);
TYPE countBag(struct DList *bag);
struct DLink * containsBag (struct DList *bag, TYPE val);
int countBag(struct DList *bag);

/*----------------------------------------------*/
int main(int argc, char **argv)
{
   /* Bag implemented as a doubly linked list */
   struct DList *bag = (struct DList *) malloc(sizeof(struct DList)); 
   assert(bag);

   int i;
   TYPE val;
   int  size = atoi(argv[1]); /* input argument is the size of Bag */

   assert(size >= 0);

   srand(time(NULL)); /*initialize random generator*/

   initDList(bag); /*initialize Bag*/

   for(i=1; i<=size; i++)
   {
      val = (TYPE) rand() % 4;
      addBackDList(bag, val); /*add val to back of Bag*/

   }
   printf("\nOriginal Bag:\n");
   _printDList(bag); /*print Bag */


   int count = countBag(bag);/*counts distinct values in Bag*/

   printf("\nBag has %d distinct values:\n", count);
   
   val = (TYPE) rand() % 4;

   removeAllBag(bag, val); /*remove all elements with val from Bag*/

   printf("\nAfter removing one element with value %d from Bag:\n", val);
   _printDList(bag); /*print Bag*/

   count = countBag(bag);/*counts distinct values in Bag*/

   printf("\nBag has %d distinct values:\n", count);

   return 0;
}


/*----------------------------------------------*/
/*Initialize doubly linked list*/
void initDList (struct DList *dl) {
   dl->frontSentinel = (struct DLink *) malloc(sizeof(struct DLink));
   assert(dl->frontSentinel != 0);
   dl->backSentinel = (struct DLink *) malloc(sizeof(struct DLink));
   assert(dl->backSentinel);
   dl->frontSentinel->next = dl->backSentinel;
   dl->backSentinel->prev = dl->frontSentinel;
   dl->size = 0;
}

/*----------------------------------------------*/
/*Free all memory occupied by a doubly linked list*/
void freeDList (struct DList *dl) {
   while (dl->size > 0) _removeDLink (dl, dl->frontSentinel->next);
   free (dl->frontSentinel);
   free (dl->backSentinel);
   dl->frontSentinel = dl->backSentinel = NULL;
}

/*----------------------------------------------*/
/*Add val to the front of a doubly linked list*/
void addFrontDList (struct DList *dl, TYPE val)
   { _addDLink(dl, dl->frontSentinel->next, val); }

/*----------------------------------------------*/
/*Add val to the back of a doubly linked list*/
void addBackDList (struct DList *dl, TYPE val)
{ _addDLink(dl, dl->backSentinel, val); }

/*----------------------------------------------*/
/*Add val before lnk to a doubly linked list*/
void _addDLink (struct DList *dl, struct DLink *lnk, TYPE val) {
   assert(dl && lnk);
   struct DLink *new = (struct DLink *) malloc(sizeof(struct DLink)); 
   assert(new);
   new->value = val; 
   new->next = lnk; 
   new->prev = lnk->prev; 
   lnk->prev->next = new; 
   lnk->prev = new;
   dl->size++; 
}

/*----------------------------------------------*/
/*Print doubly linked list*/
void _printDList(struct DList *dl){ 
   assert(dl);
   struct DLink *current = dl->frontSentinel->next;
   printf("\n");   
   while (current != dl->backSentinel){  
      printf("%d ", current->value);
      current = current->next;
   }
   printf("\n"); 
}


/*----------------------------------------------*/
/*Remove all elements with val from Bag implemented as a doubly linked list*/
/*input:
    bag -- pointer to Bag
    val -- value to be removed from Bag
*/
void removeAllBag (struct DList *bag, TYPE val){ 
   assert(bag);
   struct DLink *lnk = containsBag(bag, val);
   while (lnk){ 
      _removeDLink(bag, lnk);
      lnk = containsBag(bag, val);
   }
}

/*----------------------------------------------*/
/*Check if val is in Bag*/
/*input:
    bag -- pointer to Bag
    val -- value to be found in Bag
  output:
    NULL if val is not in Bag, or
    pointer to link that contains val in Bag
*/
struct DLink * containsBag (struct DList *bag, TYPE val) 
{
   assert(bag); 

   /*FIX ME*/
   struct DLink* curr;
   curr = bag->frontSentinel->next;
   while (curr != bag->backSentinel) {
      if (EQ(curr->value, val)) {
         return curr;
      }
      curr = curr->next;
   }
   return NULL;
}


/*----------------------------------------------*/
/*Remove a link of Deque implemented as a doubly linked list*/
void  _removeDLink (struct DList *dq, struct DLink *lnk) 
{
   assert(dq && lnk);

   lnk->next->prev = lnk->prev;
   lnk->prev->next = lnk->next;
   lnk->next = NULL;
   lnk->prev = NULL;
   free(lnk);
   dq->size--;

}


/*----------------------------------------------*/
/*Count the total number of distinct values in Bag*/
/*After returning from the function no new memory is occupied*/
/*input: 
    bag -- pointer to Bag
  output:
    return the total number of distinct values in Bag
*/
int countBag(struct DList *bag) 
{  
   assert(bag);

   struct DList* uniques;
   uniques = (struct DList*) malloc(sizeof(struct DList));
   initDList(uniques);
   {
      struct DLink * curr;
      curr = bag->frontSentinel->next;
      while (curr != bag->backSentinel) {
         if (containsBag(uniques, curr->value) == NULL) {
            addFrontDList(uniques, curr->value);
         }
         curr = curr->next;
      }
   }
   int count;
   count = uniques->size;
   freeDList(uniques);
   return count;

   
}

struct DList* unionMerge(struct DList* a, struct DList* b) {
   assert(a && b);
   struct DList* joined;
   joined = (struct DList*)malloc(sizeof(struct DList));
   initDList(joined);
   {
      struct DLink* curr;
      curr = a->frontSentinel->next;
      while (curr != a->backSentinel) {
         addBackDList(joined, curr->value);
         curr = curr->next;
      }
   }
   {
      struct DLink* curr;
      curr = b->frontSentinel->next;
      while (curr != b->backSentinel) {
         addBackDList(joined, curr->value);
         curr = curr->next;
      }
   }
   return joined;
}