#include <stdio.h>
#include <stdlib.h>

#define p void*
#define _ void*
#define untype(e) ((void**)e)
#define forever while(1)

void swap(_ x, _ y) {
    int temp = *(int*)y;
    *y = *x;
    *x = temp;
}

typedef struct {
    int value;
    struct Node* next;
    struct Node* prev;
} Node;
// struct Node {
//     int value;
//     struct Node* next;
//     struct Node* prev;
// };

void push_ll(struct {int value; void* next;} *ll) {

}

struct Node* reverse_dll(struct {int value; void* next; void* prev;} *dll) {
    struct {int value; void* next; void* prev;}* curr;
    curr = dll;
    if (dll == NULL) return NULL;
    while (curr != NULL) {
        // swap(&curr->prev, &curr->next);

        Node* temp;
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;

        curr = curr->prev;
    }
    return curr;
}

struct Node* make_dll() {
    Node* curr;
    Node* last;
    Node* head;
    last = NULL;

    int i;
    for (i = 0; i < 20; i++) {
        curr = (Node*)malloc(sizeof(Node));
        if (i == 0) head = curr;
        curr->value = i;
        curr->next = NULL;
        if (last == NULL) {
            last = curr;
            continue;
        }
        last->next = curr;
        curr->prev = last;
        last = curr;
    }
    curr->next = NULL;
    return head;
}

void print_ll(struct {int value; void* next;} *ll) {
    Node* curr;
    curr = ll;
    while (curr != NULL) {
        printf("[ %d ]\n", curr->value);
        curr = curr->next;
    }
}

int main() {
    Node* ll;
    ll = make_dll();
    print_ll(ll);
    ll = reverse_dll(ll);
    print_ll(ll);
    return 0;
}