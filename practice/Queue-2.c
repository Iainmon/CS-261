/* ENTER YOUR FIRST AND LAST NAME:      */

/* TO COMPILE, ENTER:  gcc -Wall -ansi -o prog Queue.c */

/* TO RUN, ENTER PROGRAM ARGUMENTS: CAPACITY, SIZE */
/* FOR EXAMPLE:  ./prog 10 4*/

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
void addQueue(struct Deque *q, TYPE val);
TYPE removeQueue(struct Deque *q);

/*----------------------------------------------*/
void _doubleCapacityDeque(struct Deque *dq);
void _printDeque(struct Deque *dq);

/*----------------------------------------------*/
int main(int argc, char **argv)
{
    struct Deque q;
    int i;
    TYPE val;
    int capacity = atoi(argv[1]);
    int size = atoi(argv[2]);

    assert(capacity > 0 && size >= 0);

    srand(time(NULL)); /*initialize random generator*/

    initDeque(&q, capacity); /*initialize Queue*/

    for (i = 1; i <= size; i++)
    {
        val = (TYPE)rand() % 5;
        addQueue(&q, val); /*add val to Deque*/
    }

    printf("Queue before remove:\n");
    _printDeque(&q); /*print all elements*/

    val = removeQueue(&q);

    printf("The first element of Queue was  %d\n", val);

    printf("Queue after removing the first element:\n");
    _printDeque(&q); /*print all elements*/

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

/*----------------------------------------------*/
/* Print all elements of a deque starting from the front */
/* input arguments:
  dq -- pointer to deque
*/
void _printDeque(struct Deque *dq)
{
    assert(dq);
    int i;

    printf("FRONT: ");
    for (i = 0; i < dq->size; i++)
        printf("%d ", dq->data[(dq->front + i) % dq->capacity]);

    printf(" :END\n");
}

/*----------------------------------------------*/
/* Return and remove the first element of Queue */
/* input arguments:  q -- pointer to Queue
   output :  val -- value of the first element of Queue
 */
TYPE removeQueue(struct Deque *q)
{
    TYPE val; /*auxiliary variable*/

    /* FIX ME */

    val = q->data[q->front];
    q->front = q->front + 1 % q->capacity;
    q->size--;
    return val;
}

/*----------------------------------------------*/
/* Add a new element to Queue */
/* input arguments:
  q -- pointer to Queue
  val -- value of the data element to be added
*/
void addQueue(struct Deque *q, TYPE val)
{

    /* FIX ME */
    if (q->size >= q->capacity)
    {
        _doubleCapacityDeque(q);
    }
    q->data[q->front + q->size % q->capacity] = val;
    q->size++;
}

struct Deque *concat(struct Deque *dq1, struct Deque *dq2)
{
    assert(dq1 != NULL && dq2 != NULL);
    struct Deque *joined;
    joined = (struct Deque *)malloc(sizeof(struct Deque));
    assert(joined != NULL);
    initDeque(joined, dq1->size + dq2->size);
    int i, j;
    i = 0;
    j = 0;
    while (1)
    {
        if (i < dq1->size)
        {
            addQueue(joined, dq1->data[(dq1->front + i) % dq1->capacity]);
            ++i;
        }
        if (j < dq2->size)
        {
            addQueue(joined, dq2->data[(dq2->front + j) % dq2->capacity]);
            ++j;
        }
        if (i >= dq1->size && j >= dq2->size)
        {
            break;
        }
    }
    return joined;
}