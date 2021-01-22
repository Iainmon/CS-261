#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int

struct List {
    TYPE value;
    struct List* tail;
};

struct List* init() {
    return malloc(sizeof(struct List));
}
struct List* caboose(struct List* lis) {
    if (lis == NULL) return NULL;
    struct List* curr;
    curr = lis;
    while (curr->tail != NULL) {
        curr = curr->tail;
    }
    return curr;
}
struct List* append(struct List* lis, TYPE val) {
    struct List* next;
    next = init();
    next->value = val;
    if (lis == NULL) {
        lis = next;
    } else {
        struct List* back;
        back = caboose(lis);
        back->tail = next;
    }
    return lis;
}
bool has(struct List* lis, TYPE val) {
    struct List* curr;
    curr = lis;
    while (curr != NULL) {
        if (curr->value == val) {
            return true;
        }
        curr = curr->tail;
    }
    return false;
}

struct LinkedList {
    struct List* data;
    int size;
};

struct Queue {
    struct List* head;
    struct List* tail;
    int size;
};

struct Deque {
    struct List* front;
    struct List* back;
    int size;
};