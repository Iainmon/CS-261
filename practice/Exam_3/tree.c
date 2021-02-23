#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define TYPE int
#define LT(A,B) (A < B)
#define GT(A,B) (A>B)
#define EQ(A,B) (A==B)

struct Tree {
    int value;
    struct Tree* left;
    struct Tree* right;
};

struct BSTree {
    struct Tree* root;
    int count;
};

struct List {
    struct Tree* value;
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


struct Tree* pop_back(struct Deque* dq) {
    assert(dq != NULL);
    if (dq->size < 1) { return NULL; }
    struct List * old;
    old = dq->back;
    struct Tree* back;
    back = old->value;
    if (old->prev != NULL) {
        old->prev->next = NULL;
        dq->back = old->prev;
    }
    free(old);
    dq->size--;
    return back;
}
struct Tree* pop_front(struct Deque* dq) {
    assert(dq != NULL);
    if (dq->size < 1) { return NULL; }
    struct List * old;
    old = dq->front;
    struct Tree* back;
    back = old->value;
    if (old->next != NULL) {
        old->next->prev = NULL;
        dq->front = old->next;
    }
    free(old);
    dq->size--;
    return back;
}

void push_front(struct Deque* dq, struct Tree* tr) {
    assert(dq != NULL);
    struct List *newLink = (struct List*)malloc(sizeof(struct List));
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

struct Tree* insert_bst(struct Tree* tr, TYPE val) {
    if (tr == NULL) {
        struct Tree* newNode;
        newNode = (struct Tree*)malloc(sizeof(struct Tree));
        assert(newNode);
        newNode->value = val;
        return newNode;
    }
    if (LT(val, tr->value)) {
        tr->left = insert_bst(tr->left, val);
    } else if (GT(val, tr->value)) {
        tr->right = insert_bst(tr->right, val);
    }
    return tr;
}

void pre_order_print(struct Tree* tr) {
    if (tr == NULL) { return; }
    
    printf("%d\n", tr->value);
    pre_order_print(tr->left);
    pre_order_print(tr->right);
}
void in_order_print(struct Tree* tr) {
    if (tr == NULL) { return; }

    in_order_print(tr->left);
    printf("%d\n", tr->value);
    in_order_print(tr->right);

}
void post_order_print(struct Tree* tr) {
    if (tr == NULL) { return; }

    post_order_print(tr->left);
    post_order_print(tr->right);
    printf("%d\n", tr->value);
}

void left_trav(struct Tree* tr) {
    if (tr == NULL) {return;}
    printf("%d\n", tr->value);
    left_trav(tr->left);
}

void bfs(struct BSTree* bst, TYPE val) {
    assert(bst != NULL);
    struct Tree* curr;
    struct Deque* queue;
    queue = init_dq();
    push_front(queue, bst->root);
    while (queue->size > 0) {
        curr = pop_back(queue);
        if (curr == NULL) { continue; }
        /*if (EQ(curr->value, val)) {
            free(queue);
            printf("found %d\n", curr->value);
            return;
        }*/
        printf("%d\n", curr->value);
        push_front(queue, curr->left);
        push_front(queue, curr->right);
    }
}


void dfs(struct BSTree* bst, TYPE val) {
    assert(bst != NULL);
    struct Tree* curr;
    struct Deque* stack;
    stack = init_dq();
    push_front(stack, bst->root);
    while (stack->size > 0) {
        curr = pop_front(stack);
        if (curr == NULL) { continue; }
        /*if (EQ(curr->value, val)) {
            free(stack);
            printf("found %d\n", curr->value);
            return;
        }*/
        printf("%d\n", curr->value);
        push_front(stack, curr->right);
        push_front(stack, curr->left);

    }
}

