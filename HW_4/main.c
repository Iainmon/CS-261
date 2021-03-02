#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include "avl.h"
#include "include.c"


int FindMinPath(struct AVLTree *tree, TYPE *path);
void printBreadthFirstTree(struct AVLTree *tree);


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
	printf("TO INLINE CODE BEFORE SUB\n");
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


  
/* --------------------
Finds the minimum-cost path in an AVL tree
   Input arguments: 
        tree = pointer to the tree,
        path = pointer to array that stores values of nodes along the min-cost path, 
   Output: return the min-cost path length 

   pre: assume that
       path is already allocated sufficient memory space 
       tree exists and is not NULL
*/
int FindMinPath(struct AVLTree *tree, TYPE *path)
{
               /* FIX ME */
    int i, lhs_diff, rhs_diff;
	struct AVLnode *curr, *next;
	assert(tree);
	i = 0;
	curr = tree->root;
	while (curr != NULL) {
		/* Compare values */
		if (curr->left != NULL)
		{ lhs_diff = abs(curr->val - curr->left->val);}
		if (curr->right != NULL)
		{ rhs_diff = abs(curr->val - curr->right->val);}

		if (curr->right == NULL)
		{ rhs_diff = lhs_diff + 1;}
		if (curr->left == NULL)
		{ lhs_diff = rhs_diff + 1;}

		/* Make descision */
		if (lhs_diff < rhs_diff) {
			next = curr->left;
		} else {
			next = curr->right;
		}

		path[i] = curr->val;
		++i;
		curr = next;
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



