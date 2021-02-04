#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define TYPE int

struct List {
    TYPE val;
    struct List* prev;
    struct List* next;
};

struct List* initList() {
    struct List* lis;
    lis = (struct List*)malloc(sizeof(struct List));
    assert(lis != NULL);
    lis->prev = NULL;
    lis->next = NULL;
    return lis;
}

struct Deque {
    struct List* front;
    struct List* back;
    int size;
};

struct Deque* init() {
    struct Deque* dq;
    dq = (struct Deque*)malloc(sizeof(struct Deque));
    assert(dq != NULL);
    dq->size = 0;
    dq->front = NULL;
    dq->back = NULL;
}

TYPE top(struct Deque* dq) {
    assert(dq->size > 0);
    return dq->front->val;
}

TYPE back(struct Deque* dq) {
    assert(dq->size > 0);
    return dq->back->val;
}

void push_front(struct Deque* dq, TYPE val) {
    struct List* front;
    front = initList();
    front->val = val;
    front->next = dq->front;
    dq->front = front;
    dq->size++;
}

void push_back(struct Deque* dq, TYPE val) {
    struct List* back;
    back = initList();
    back->val = val;
    back->prev = dq->back;
    dq->back = back;
    dq->size++;
}

void pop_front(struct Deque* dq) {
    assert(dq->size > 0);
    struct List* old;
    old = dq->front;
    dq->front = dq->front->next;
    dq->front->prev = NULL;
    dq->size--;
    free(old);
}

void pop_back(struct Deque* dq) {
    assert(dq->size > 0);
    struct List* old;
    old = dq->back;
    dq->back = dq->back->prev;
    dq->back->next = NULL;
    dq->size--;
    free(old);
}