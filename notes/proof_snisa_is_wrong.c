#include <stdio.h>
#include <assert.h>

struct Link {
    int value;
    struct Link * next;
};

struct ListStack {
    struct Link * sentinel;
};

void pushStack_ref(struct ListStack* stk, int val) {
    struct Link * new = (struct Link *)malloc(sizeof(struct Link));
    assert(new != NULL);
    new->value = val;
    new->next = stk->sentinel->next;
    stk->sentinel->next = new;
}

void pushStack_val(struct ListStack stk, int val) {
    struct Link * new = (struct Link *)malloc(sizeof(struct Link));
    assert(new != NULL);
    new->value = val;
    new->next = stk.sentinel->next;
    stk.sentinel->next = new;
}

struct Link* cons_list(int n) {
    struct Link* head;
    struct Link* curr;
    while (n >= 0) {
        curr = malloc(sizeof(struct Link));
        curr->value = n;
        curr->next = head;
        head = curr;
        --n;
    }
    return head;
}

void print_list(struct Link* lis) {
    while (lis != NULL) {
        printf("%d\n", lis->value);
        lis = lis->next;
    }
}

int main() {
    struct ListStack stack;
    stack.sentinel = cons_list(5);
    printf("Before adding\n");
    print_list(stack.sentinel);
    printf("Adding via reference\n");
    pushStack_ref(&stack, 88);
    print_list(stack.sentinel);
    printf("Adding via reference\n");
    pushStack_val(stack, 99);
    print_list(stack.sentinel);
}