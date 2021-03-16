#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TYPE int

struct Heap {
    TYPE *data;
    int size;
    int capacity;
};

struct Heap init_heap(int n)
{
    struct Heap *heap;
    heap = (struct Heap*)malloc(sizeof(struct Heap));
    assert(heap);
    heap->data = (TYPE*)malloc(sizeof(TYPE)*n);
    assert(heap->data);
    heap->capacity = n;
    heap->size = 0;
    return heap;
}

/*
    Bubbles up the heap and corrects a violation of the heap property. (percolate up)
    This implementation is for a min heap.
*/
void adjust_heap_bottom_to_top(struct Heap *heap, int i)
{
    TYPE temp;
    int parent;
    assert(heap);
    parent = (i - 1) / 2;

    if (parent < 0 || i < 0) { return; }

    if (heap->data[parent] > heap->data[i])
    {
        /* This is the swap */
        temp = heap->data[parent];
        heap->data[parent] = heap->data[i];
        heap->data[i] = temp;

        adjust_heap_bottom_to_top(heap, parent);
    }
}


/*
    Percolates down
*/
void adjust_heap_top_to_bottom(struct Heap *heap, int i)
{
    TYPE temp;
    int right, left, smallest;
    assert(heap);
    smallest = i;
    left = (i * 2) + 1;
    right = (i * 2) + 2;

    if (left >= heap->size || left < 0) { left = -1; }
    if (right >= heap->size || right < 0) { right = -1; }

    if (left != -1 && heap->data[left] < heap->data[smallest]) { smallest = left; }
    if (right != -1 && heap->data[right] < heap->data[smallest]) { smallest = right; }

    if (smallest != i)
    {
        /* Preform swap */
        temp = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = temp;

        adjust_heap_top_to_bottom(heap, smallest);
    }
}