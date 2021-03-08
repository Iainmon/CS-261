#include "avl.h"

struct List {
    struct AVLnode* value;
    struct List* prev;
    struct List* next;
};

struct Deque {
    struct List* front;
    struct List* back;
    int size;
};

struct List* new_list_node() {
    return (struct List*)malloc(sizeof(struct List));
}
struct Deque* init_dq() {
    struct Deque* dq = (struct Deque*) malloc(sizeof(struct Deque));
    dq->back = NULL;
    dq->front = NULL;
    dq->size = 0;
    return dq;
}

struct AVLnode* pop_back(struct Deque* dq) {
    struct List * old;
    struct AVLnode* back;
    assert(dq != NULL);
    if (dq->size < 1) { return NULL; }
    old = dq->back;
    back = old->value;
    if (old->prev != NULL) {
        old->prev->next = NULL;
        dq->back = old->prev;
    }
    free(old);
    dq->size--;
    return back;
}

void push_front(struct Deque* dq, struct AVLnode* tr) {
    struct List *newLink;
    assert(dq != NULL);
    newLink = (struct List*)malloc(sizeof(struct List));
    newLink->value = tr;
    newLink->next = dq->front;
    newLink->prev = NULL;
    if (dq->size < 1) {
        dq->back = newLink;
    } else {
        dq->front->prev = newLink;
    }
    dq->front = newLink;
    dq->size++;
}

