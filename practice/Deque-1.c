/* ENTER YOUR FIRST AND LAST NAME:      */

/* TO COMPILE, ENTER:  gcc -Wall -ansi -o prog Deque.c */

/* TO RUN, ENTER PROGRAM ARGUMENTS: CAPACITY, SIZE, FLAG */
/* FOR EXAMPLE:  ./prog 10 4 -1*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TYPE int
#define EQ(a, b) (a == b)

struct Deque
{
    TYPE *data;
    int size;     /* number of elements in data */
    int capacity; /* memory capacity of the deque */
    int front;    /* index of the front end of deque  */
};

/*----------------------------------------------*/
void initDeque(struct Deque *dq, int cap);
void addFrontDeque(struct Deque *dq, TYPE val);
void printDeque(struct Deque *dq);
void removeBackAllDeque(struct Deque *dq, int flag);
/*----------------------------------------------*/
void _doubleCapacityDeque(struct Deque *dq);

/*----------------------------------------------*/
int main(int argc, char **argv)
{
    struct Deque dq;
    int i;
    TYPE val;
    int capacity = atoi(argv[1]);
    int size = atoi(argv[2]);
    int flag = atoi(argv[3]);

    assert(capacity > 0 && size >= 0);

    srand(time(NULL)); /*initialize random generator*/

    initDeque(&dq, capacity); /*initialize Deque*/

    for (i = 1; i <= size; i++)
    {
        val = (TYPE)rand() % 5;
        addFrontDeque(&dq, val); /*add val to Deque*/
    }

    printf("Deque before remove:\n");
    printDeque(&dq); /*print all elements*/

    removeBackAllDeque(&dq, flag);

    printf("Deque after remove:\n");
    printDeque(&dq); /*print all elements*/

    return 0;
}

/*----------------------------------------------*/
/* Initialize Deque */
/* input arguments:
  dq -- pointer to deque
  cap = capacity of a memory block to be allocated
*/
void initDeque(struct Deque *dq, int cap)
{
    assert(dq);
    dq->capacity = cap;
    dq->size = dq->front = 0;
    dq->data = (TYPE *)malloc(dq->capacity * sizeof(TYPE));
    assert(dq->data != 0);
}

/*----------------------------------------------*/
/* input arguments:
  dq -- pointer to deque
  val -- value of the data element to be added
*/
void addFrontDeque(struct Deque *dq, TYPE val)
{
    assert(dq);
    if (dq->size == dq->capacity)
        _doubleCapacityDeque(dq);
    dq->front--;
    if (dq->front < 0)
        dq->front += dq->capacity;
    dq->data[dq->front] = val;
    dq->size++;
}

/*----------------------------------------------*/
/* Double the memory capacity of a deque */
void _doubleCapacityDeque(struct Deque *dq)
{
    assert(dq);
    int j;
    TYPE *oldData = dq->data;       /*memorize old data*/
    int oldFront = dq->front;       /*memorize old index of the front end of deque*/
    int oldSize = dq->size;         /*memorize old size*/
    int oldCapacity = dq->capacity; /*memorize old capacity*/
    initDeque(dq, 2 * oldCapacity); /*new memory allocation*/
    for (j = 0; j < oldSize; j++)
    { /*copy back old data*/
        dq->data[j] = oldData[oldFront++];
        if (oldFront >= oldCapacity)
            oldFront = 0;
    }
    free(oldData);
    dq->size = oldSize;
}

#define ind(i) ((dq->front + i) % dq->capacity)

/*----------------------------------------------*/
/* Print all elements of a deque starting from the front */
/* input arguments:
  dq -- pointer to deque
*/
void printDeque(struct Deque *dq)
{
    assert(dq);

    /* FIX ME */
    int i;
    i = 0;
    while (i < dq->size)
    {
        printf("%d\n", dq->data[ind(i)]);
        ++i;
    }
}

/*----------------------------------------------*/
/* Remove one or all element(s) from the back of Deque */
/* input arguments:
  dq -- pointer to deque
  flag -- flag = 1:remove only one element at the back
          flag = -1:remove all repetitions of the element at the back
*/
void removeBackAllDeque(struct Deque *dq, int flag)
{
    assert(dq && (flag == 1 || flag == -1));
    if (dq->size < 1)
        return;
    if (flag == 1)
    {
        dq->size--;
        return;
    }

    TYPE curr;
    curr = dq->data[dq->front + dq->size - 1 % dq->capacity];
    while (curr == dq->data[dq->front + dq->size - 1 % dq->capacity])
    {
        dq->size--;
    }
    /* int idx = (dq->size + i) % dq->capacity; */
    /*TYPE curr;
  curr = dq->data[ind(dq->size)];
  while (curr == dq->data[ind(dq->size)]) {
     dq->size--;
  }*/
    /*TYPE curr;
  curr = dq->data[dq->front + dq->size-1 % dq->capacity];
  while (1) {
     if (curr != dq->data[dq->front + dq->size-1 % dq->capacity]) {
        break;
     }
     dq->size--;
  }*/
    /* FIX ME */
}
