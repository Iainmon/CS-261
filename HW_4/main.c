#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include "avl.h"


#define min(a,b) (a < b ? a : b)

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

int FindMinPath(struct AVLTree *tree, TYPE *path);
void printBreadthFirstTree(struct AVLTree *tree);
int findMinPath(struct AVLnode *root, TYPE *path);
void push_front(struct Deque* dq, struct AVLnode* tr);
struct AVLnode* pop_back(struct Deque* dq);
struct Deque* init_dq();
struct List* new_list_node();
/* -----------------------
The main function
  param: argv = pointer to the name (and path) of a file that the program reads for adding elements to the AVL tree
*/
int main(int argc, char** argv) {

	FILE *file;
	int len, i;
	TYPE num; /* value to add to the tree from a file */
	struct timeval stop, start; /* variables for measuring execution time */
	int pathArray[100];  /* static array with values of nodes along the min-cost path of the AVL tree. The means that the depth of the AVL tree cannot be greater than 100 which is  sufficient for our purposes*/

	struct AVLTree *tree;
	
	tree = newAVLTree(); /*initialize and return an empty tree */
	
	file = fopen(argv[1], "r"); 	/* filename is passed in argv[1] */
	assert(file != 0);

	/* Read input file and add numbers to the AVL tree */
	while((fscanf(file, "%i", &num)) != EOF){
		addAVLTree(tree, num);		
	}
	/* Close the file  */
	fclose(file);

        printf("\nThe AVL tree has %d nodes.\n",tree->cnt);
	
	printf("\nPrinting the AVL tree breadth-first : \n");
	printBreadthFirstTree(tree);

	gettimeofday(&start, NULL);

	/* Find the minimum-cost path in the AVL tree*/
	len = FindMinPath(tree, pathArray);
	
	gettimeofday(&stop, NULL);

	/* Print out all numbers on the minimum-cost path */
	printf("\n\nThe minimum-cost path has %d nodes printed top-down from the root to the leaf: \n", len);
	for(i = 0; i < len; i++)
		printf("%d ", pathArray[i]);
	printf("\n");

	printf("\nYour execution time to find the mincost path is %f microseconds\n", (double) (stop.tv_usec - start.tv_usec));

        /* Free memory allocated to the tree */
	deleteAVLTree(tree); 
	
	return 0;
}

void _findMinPath(struct AVLnode *sub_tree_root, int path_cost, int *parent_key, int *global_min, struct AVLnode** min_leaf)
{
	path_cost += abs(*parent_key - sub_tree_root->val);
	if (path_cost >= *global_min) { return; }
	if (sub_tree_root->height < 1)
	{
		if (path_cost < *global_min) {
			*global_min = path_cost;
			*min_leaf = sub_tree_root;
		}
		return;
	}

	if (sub_tree_root->left != NULL) { _findMinPath(sub_tree_root->left, path_cost, &sub_tree_root->val, global_min, min_leaf); }
	if (sub_tree_root->right != NULL) { _findMinPath(sub_tree_root->right, path_cost, &sub_tree_root->val, global_min, min_leaf); }

}

int FindMinPath(struct AVLTree *tree, TYPE* path) {
	struct AVLnode *min_leaf, *curr;
	int i;
	int global_min; global_min = 2147483647;
	assert(tree);
	if (tree->root == NULL) return 0;
	_findMinPath(tree->root, 0, &tree->root->val, &global_min, &min_leaf);
	/*printf("min leaf: %d\n", min_leaf->val);
	printf("min cost  : %d\n", global_min);*/

	i = 0;
	curr = tree->root;
	while (1) {
		path[i] = curr->val;
		++i;
		/*if (min_leaf->val == curr->val && curr->height == 0) { break; }*/
		if (min_leaf == curr) { return i; }
		/*if (min_leaf->val == curr->val) { break; }*/
		/*if (curr->height == 0) { break; }*/
		if (min_leaf->val < curr->val) {
			curr = curr->left;
		} else {
			curr = curr->right;
		}
	} 
	return i;
}

/* -----------------------
Printing the contents of an AVL tree in breadth-first fashion
  param: pointer to a tree
  pre: assume that tree was initialized well before calling this function
*/
void printBreadthFirstTree(struct AVLTree *tree)
{
   
    /* FIX ME */
	struct AVLnode* curr;
    struct Deque* queue;
	assert(tree != NULL);

    queue = init_dq();
    push_front(queue, tree->root);
    while (queue->size > 0) {
        curr = pop_back(queue);
        if (curr == NULL) { continue; }
        /*if (EQ(curr->value, val)) {
            free(queue);
            printf("found %d\n", curr->value);
            return;
        }*/
        printf("%d\n", curr->val);
        push_front(queue, curr->left);
        push_front(queue, curr->right);
    }
	free(queue);
}




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
