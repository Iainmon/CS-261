/*
Iain Moncrief
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TYPE double
struct Node
{
    TYPE val;           /*node’s value*/
    struct Node *left;  /*pointer to the left child*/
    struct Node *right; /*pointer to the right child*/
};
struct Tree
{
    struct Node *root;
    int size;
};
/* Breadth-last traversal of a binary tree
- Input: tree = pointer to a binary tree.
- Pre-conditions: tree was initialized well and exists in memory, but may be
empty.
- Constraints: time complexity <= O(n); no new data structures allowed,
no new memory locations can be allocated, except for a couple of integers
*/

void print_post_order(struct Node* node, int level)
{
    if (node == NULL) { return; }
    if (level < 1)
    {
        printf("%g, ", node->val);
        return;
    }
    print_post_order(node->left, level-1);
    print_post_order(node->right, level-1);

}

void max_height_of_tree(struct Node* node, int height, int *max_height)
{
    if (node == NULL) { return; }
    if (height > *max_height)
    {
        *max_height = height;
    }
    max_height_of_tree(node->left, height+1, max_height);
    max_height_of_tree(node->right, height+1, max_height);

}

void printBreadthLastBinaryTree(struct Tree *tree)
{
    int height, i;
    assert(tree);
    height = 0;
    max_height_of_tree(tree->root, 0, &height);

    i = 0;
    while (i <= height)
    {
        print_post_order(tree->root, i);
        printf("\n");
        ++i;
    }
}