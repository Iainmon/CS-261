/* ENTER YOUR FIRST AND LAST NAME:      */

/* TO COMPILE:  gcc -Wall -ansi -o prog Queue.c */

/* TO RUN, ENTER SIZE OF QUEUE */
/* FOR EXAMPLE:  ./prog 10 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int

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

/*Interface for Deque implemented as a doubly linked list*/
void initDList (struct DList *dq);
void freeDList (struct DList *dq);
void addFrontDList (struct DList *dq, TYPE val);
void addBackDList (struct DList *dq, TYPE val);
void  _removeDLink (struct DList *dq, struct DLink *lnk);
void _printDList(struct DList *dq);
void _addDLink (struct DList *dq, struct DLink *lnk, TYPE val);
/*----------------------------------------------*/
/*Interface for Queue implemented as a doubly linked list*/
void addQueue (struct DList *q, TYPE val);
struct DList *flipQueue(struct DList *q);


/*----------------------------------------------*/
int main(int argc, char **argv)
{
   /* Queue implemented as a doubly linked list */
   struct DList *q = (struct DList *) malloc(sizeof(struct DList)); 
   assert(q);

   int i;
   TYPE val;
   int  size = atoi(argv[1]); /* input argument is the size of Queue */

   assert(size >= 0);

   srand(time(NULL)); /*initialize random generator*/

   initDList(q); /*initialize Queue*/

   for(i=1; i<=size; i++)
   {
      val = (TYPE) rand() % 100;
      addQueue(q, val); /*add val to Queue*/
   }
   printf("\nOriginal Queue:\n");
   _printDList(q); /*print Queue from Front to Back*/

   q = flipQueue(q); /*reorganize Queue in the reverse order*/

   printf("\nFlipped Queue:\n");
   _printDList(q); /*print Queue from Front to Back*/

   return 0;
}


/*----------------------------------------------*/
/*Initialize Deque implemented as a doubly linked list*/
void initDList (struct DList *dq) {
   dq->frontSentinel = (struct DLink *) malloc(sizeof(struct DLink));
   assert(dq->frontSentinel != 0);
   dq->backSentinel = (struct DLink *) malloc(sizeof(struct DLink));
   assert(dq->backSentinel);
   dq->frontSentinel->next = dq->backSentinel;
   dq->backSentinel->prev = dq->frontSentinel;
   dq->size = 0;
}


/*----------------------------------------------*/
/*Free all memory occupied by Deque implemented as a doubly linked list*/
void freeDList (struct DList *dq) {
   while (dq->size > 0) _removeDLink (dq, dq->frontSentinel->next);
   free (dq->frontSentinel);
   free (dq->backSentinel);
   dq->frontSentinel = dq->backSentinel = NULL;
}


/*----------------------------------------------*/
/*Remove a link of Deque implemented as a doubly linked list*/
void  _removeDLink (struct DList *dq, struct DLink *lnk) {
   assert(dq && lnk);
   lnk->prev->next = lnk->next;
   lnk->next->prev = lnk->prev;
   free(lnk);
   dq->size--;
}

/*----------------------------------------------*/
/*Add val to the front of Deque implemented as a doubly linked list*/
void addFrontDList (struct DList *dq, TYPE val)
   { _addDLink(dq, dq->frontSentinel->next, val); }

/*----------------------------------------------*/
/*Add val to the back of Deque implemented as a doubly linked list*/
void addBackDList (struct DList *dq, TYPE val)
{ _addDLink(dq, dq->backSentinel, val); }

/*----------------------------------------------*/
/*Print from front to back Deque implemented as a doubly linked list*/
void _printDList(struct DList *dq){ 
   assert(dq);
   printf("\nFRONT: ");
   struct DLink *current = dq->frontSentinel->next;   
   while (current != dq->backSentinel){  
      printf("%d ", current->value);
      current = current->next;
   }
   printf(" :END\n");
}


/*----------------------------------------------*/
/*Add val to Queue implemented as a doubly linked list*/
/*input:
    q -- pointer to Queue
    val -- value to be added to Queue
*/
void addQueue (struct DList *q, TYPE val)
{ 

   /* FIX ME */
 
}



/*----------------------------------------------*/
/*Add val before a given link of Deque implemented as a doubly linked list*/
/*input: 
    dq -- pointer to Deque
    lnk -- pointer to a link; lnk->prev should point to the newly added link
    val -- new value to be assigned to a newly formed link in Deque
*/      
void  _addDLink (struct DList *dq, struct DLink *lnk, TYPE val) 
{
   assert(dq && lnk);

   /* FIX ME */

}


/*----------------------------------------------*/
/*Flip Queue in the reverse order*/
/*After returning from the function no new memory is occupied*/
/*input: 
    q -- pointer to Queue
  output:
    return the pointer to the corresponding flipped Queue
*/
struct DList *flipQueue(struct DList *q) 
{  

   assert(q);

   /*FIX ME*/


   

}












