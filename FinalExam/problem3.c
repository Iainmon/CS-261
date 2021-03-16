/*
Iain Moncrief
*/

#include <assert.h>
struct Element
{
    int priority; /* the lower value the higher priority */
    char string[100];
};
#define TYPE struct Element
struct DynArr
{
    TYPE *data;   /* pointer to the data array */
    int size;     /* number of elements in the array */
    int capacity; /* capacity of the array */
};
/* Percolate down a node of Heap
Input: heap -- pointer to the heap
index -- index of a node for percolating down
*/
void percolateDownHeap(struct DynArr *heap, int index)
{
    assert(heap && index < heap->size);
    int higher;
    TYPE tmp;
    int maxIdx = heap->size;
    int leftIdx = index * 2 + 1; /* left child index */
    int rghtIdx = index * 2 + 2; /* right child index */
    while (leftIdx < heap->size)
    {
        if (rghtIdx < maxIdx)
            higher = heap->data[leftIdx].priority < heap->data[rghtIdx].priority
                         ? leftIdx
                         : rghtIdx;
        else
            higher = leftIdx;
        if (heap->data[higher].priority < heap->data[index].priority)
        {
            tmp = heap->data[higher];
            heap->data[higher] = heap->data[index];
            heap->data[index] = tmp;
            index = higher;
            leftIdx = index * 2 + 1;
            rghtIdx = index * 2 + 2;
        }
        else
            leftIdx = heap->size;
    }
}
void removeAtDynArr(struct DynArr *v, int idx)
{
	int i;

	for(i = idx; i < v->size-1; ++i)
		v->data[i] = v->data[i+1];

	if(idx >= 0 && idx < v->size)
		--v->size;
}
void removeMinHeap(struct DynArr *heap, int i)
{
    int last;
    assert(heap);
    assert(heap->size > 0);
    last = (heap->size) - 1;
    /* Copy the last element to the first */
    heap->data[i] = heap->data[last];
    /* Remove last element. */
    removeAtDynArr(heap, last);
    /* Rebuild heap */
    percolateDownHeap(heap, i);
}

void remove_sub_heap(struct DynArr *heap, int i, int threshold)
{
    int left, right;
    assert(heap);
    if (i >= heap->size)
    {
        return;
    }
    left = i * 2 + 1;
    right = i * 2 + 2;

    if (left >= heap->size || left < 0)
    {
        left = -1;
    }
    if (right >= heap->size || right < 0)
    {
        right = -1;
    }

    if (left != -1 && heap->data[left].priority > threshold)
    {
        removeMinHeap(heap, left);
        remove_sub_heap(heap, left, threshold);
    }
    if (right != -1 && heap->data[right].priority > threshold)
    {
        removeMinHeap(heap, right);
        remove_sub_heap(heap, right, threshold);
    }
}

/* Remove from Heap elements with lower priority than a threshold
- Input: heap = pointer to a heap implemented as a dynamic array.
threshold = positive integer.
- Pre-conditions: heap was initialized well and exists in memory, but may be
empty. Also, heap correctly established the priority relationships among all of
its elements.
- Constraints: time complexity <= O(n log n); no new data structures allowed,
no new memory locations can be allocated, except for a couple of integers
*/
void removeThresholdHeap(struct DynArr *heap, int threshold)
{
    assert(heap && threshold > 0);
    /* FIX ME */
    remove_sub_heap(heap, 0, threshold);
}