#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct Link {
    int value;
    struct Link* next;
    struct Link* prev;
};

struct Link* initList(int size) {
    struct Link* head;
    struct Link* last; last = NULL;
    struct Link* curr;
    int i;
    i = 0;
    while (i < size) {
        curr = (struct Link*)malloc(sizeof(struct Link));
        if (last != NULL) { last->next = curr; }
        curr->value = i;
        curr->prev = last;
        curr->next = NULL;
        last = curr;
        if (i == 0) { head = curr; }
        ++i;
    }
    return head;
}

void print_list(struct Link * head) {
    while (head != NULL) {
        printf("%d\n", head->value);
        head = head->next;
    }
}

int main(int argc, char **argv) {

    struct Link* list;
    list = initList(100);
    printf("worke\n");
    print_list(list);
    return 0;
}