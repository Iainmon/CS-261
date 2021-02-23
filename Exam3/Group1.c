/* ENTER YOUR FIRST AND LAST NAME:      */
/* TO COMPILE:  gcc -Wall -ansi -o program Group1.c */
/* TO RUN, ENTER YOUR INPUT FILE NAME:  ./program input1.txt  */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int
#define LT(A,B) (A < B)
#define GT(A,B) (A>B)
#define EQ(A,B) (A==B)
#define TYPE int
struct Node
{
    TYPE val;
    struct Node *left;
    struct Node *right;
};
struct BST
{
    struct Node *root;
    int size;
};

void addBST(struct BST *tree, TYPE val);
int heightBST(struct BST *tree);
struct Node *insert_node(struct Node *tr, TYPE val);
int heightBST_recurse(struct Node * tr);

/****************************************/
int main(int argc, const char *argv[])
{
    const char *filename;
    FILE *fileptr;
    struct BST *tree = (struct BST *)malloc(sizeof(struct BST));
    assert(tree);
    tree->root = 0;
    tree->size = 0;
    int value, height;

    if (argc == 2)
        filename = argv[1];
    else
        filename = "input.txt"; /* default file name */
    fileptr = fopen(filename, "r");

    printf("Adding nodes to BST with values from the file: %s\n", filename);
    while (!feof(fileptr))
    {
        fscanf(fileptr, "%d", &value);
        addBST(tree, value);
    }

    height = heightBST(tree);
    printf("The tree height is %d\n", height);

    return 0;
}

/****************************************/
/* Add a new node to BST */
/*
    input: tree -- pointer to BST,
           val -- value to be added to BST
    pre-conditions: BST was initialized well
    constraint: complexity <= O(log n)
*/
void addBST(struct BST *tree, TYPE val)
{
    assert(tree);

    /* FIX ME */
    tree->root = insert_node(tree->root, val);
    tree->size++;
}

struct Node *insert_node(struct Node *tr, TYPE val)
{
    if (tr == NULL)
    {
        struct Node *newNode;
        newNode = (struct Node *)malloc(sizeof(struct Node));
        assert(newNode);
        newNode->val = val;
        return newNode;
    }
    if (LT(val, tr->val))
    {
        tr->left = insert_node(tr->left, val);
    }
    else if (GT(val, tr->val))
    {
        tr->right = insert_node(tr->right, val);
    }
    return tr;
}

/****************************************/
/* Compute the height of BST */
/*
    input: tree -- pointer to BST
    output: the height of BST is returned
    pre-conditions: BST was initialized well
    requirement: If the tree is empty, return -1
    constraints: complexity <= O(n), no new memory allocation 
*/
int heightBST(struct BST *tree)
{
    assert(tree);

    /* FIX ME */
    return heightBST_recurse(tree->root);
}

int heightBST_recurse(struct Node * tr) {
    if (tr == NULL) { return -1; }
    int lhs, rhs;
    lhs = heightBST_recurse(tr->left);
    rhs = heightBST_recurse(tr->right);
    if (lhs > rhs) {
        return lhs + 1;
    } else {
        return rhs +1;
    }
}
