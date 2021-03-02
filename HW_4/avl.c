#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "avl.h"

#define max(a,b) ((a>b)?a:b)

/* Alocate and initialize AVL tree structure. */
struct AVLTree * newAVLTree()
{
	struct AVLTree *tree = (struct AVLTree *)malloc(sizeof(struct AVLTree));
	assert(tree != 0);
	
	initAVLTree(tree);
	return tree;
}

/* Initialize AVL tree structure. */
void initAVLTree(struct AVLTree *tree)
{
	tree->cnt = 0;
	tree->root = 0;

}

void _freeAVL(struct AVLnode *node)
{
	if (node != 0) {
		_freeAVL(node->left);
		_freeAVL(node->right);		
		free(node);
	}
}

/* Deallocate nodes in AVL tree. */
void clearAVLTree(struct AVLTree *tree)
{
	_freeAVL(tree->root);
	tree->root = 0;
	tree->cnt  = 0;
}

/* Deallocate nodes in AVL tree and deallocate the AVL tree structure. */
void deleteAVLTree(struct AVLTree *tree)
{
	clearAVLTree(tree);
	free(tree);
}


/* return height of current node */
int h(struct AVLnode *current)
{
	if (current == 0)
		return -1;
	return current->height;
}

/* set height for current node */
void setHeight (struct AVLnode * current)
{
	int lch = h(current->left);
	int rch = h(current->right);
	if (lch < rch)
		current->height = 1 + rch;
	else
		current->height = 1 + lch;
}

/* return balance factor value */
int bf(struct AVLnode * current)
{
	if (current == 0) { return 0; }
	return h(current->right) - h(current->left);
}

/* left-rotate subtree of current node */
struct AVLnode * rotateLeft(struct AVLnode * current)
{
	struct AVLnode * newtop;
	newtop = current->right;


    /* FIX ME */

	current->right = newtop->left;
	newtop->left = current;
	/*current->height = newtop->height - 1;*/
	setHeight(current);
	setHeight(newtop);

	return newtop;
}

/* right-rotate subtree of current node */
struct AVLnode * rotateRight(struct AVLnode * current)
{
	struct AVLnode * newtop = current->left;


        /* FIX ME */
	current->left = newtop->right;
	newtop->right = current;
	/* current->height = newtop->height - 1;*/
	setHeight(current);
	setHeight(newtop);

	return newtop;
}

/* balance subtree of current node */
struct AVLnode * _balance(struct AVLnode * current)
{
	int rbf;
	rbf = bf(current);
	


       /* FIX ME */
	if (rbf > 1)
	{
		if (bf(current->right) < 0)
		{
			assert(current->right->left);
			current->right = rotateRight(current->right);
			assert(current->right);
			current = rotateLeft(current);
		}
		else
		{
			assert(current->right);
			current = rotateLeft(current);
		}
	}
	else if (rbf < -1)
	{
		if (bf(current->left) > 0)
		{
			assert(current->left->right);
			current->left = rotateLeft(current->left);
			assert(current->left);
			current = rotateRight(current);
		}
		else
		{
			assert(current->left);
			current = rotateRight(current);
		}
	}
	setHeight(current);
	return current;
}

/* add newValue to subtree of current node */
struct AVLnode * AVLnodeAdd(struct	AVLnode * current, TYPE newValue)
{

     /* FIX ME */
	if (current == NULL)
	{
		struct AVLnode* new_node;
		new_node = (struct AVLnode*)malloc(sizeof(struct AVLnode));
		new_node->height = 0;
		new_node->val = newValue;
		new_node->left = NULL;
		new_node->right = NULL;
		return new_node;
	}
	/* I don't think I need to be balancing each branch after adding */
	if (newValue <= current->val)
	{
		current->left = AVLnodeAdd(current->left, newValue);
		current->left = _balance(current->left);
	}
	else if (newValue > current->val)
	{
		current->right = AVLnodeAdd(current->right, newValue);
		current->right = _balance(current->right);
	}

	current = _balance(current);
	return current;
}

/* add val to AVL tree */
void addAVLTree(struct AVLTree *tree, TYPE val)
{
	tree->root = AVLnodeAdd(tree->root, val);	
	tree->cnt++;
}

/* determine if val is contained in the AVL tree */
int containsAVLTree(struct AVLTree *tree, TYPE val)
{
	struct AVLnode* cur = tree->root;

	while(cur != 0){
		if (EQ(cur->val, val))	
			return 1;
		else if (LT(val, cur->val))
			cur = cur->left;
		else
			cur = cur->right;
	}

	return 0; 
}

/* find leftmost value from subtree of current node */
TYPE _leftMost(struct AVLnode *cur)
{
	while(cur->left != 0)
		cur = cur->left;
	return cur->val;
}

/* remove leftmost node from subtree of current node */
struct AVLnode * _removeLeftmost(struct AVLnode * cur)
{
	struct AVLnode * temp;

	if(cur->left != 0){
		cur->left = _removeLeftmost(cur->left);
		return _balance(cur);
	}

	temp = cur->right;
	free(cur);
	return temp;
}

/* remove val from subtree of cur node */
struct AVLnode * _removeNode(struct AVLnode * cur, TYPE val)
{
	struct AVLnode * temp;

	if(EQ(val, cur->val)){
		if(cur->right != 0){
			cur->val = _leftMost(cur->right);
			cur->right = _removeLeftmost(cur->right);
			return _balance(cur);
		} else {
			temp = cur->left;
			free(cur);
			return temp;
		}
	} else if (LT(val, cur->val))
		cur->left = _removeNode(cur->left, val);
	else cur->right = _removeNode(cur->right, val);

	return _balance(cur);
}

/* remove val from AVL tree */
void removeAVLTree(struct AVLTree * tree, TYPE val)
{
	if(containsAVLTree(tree, val)){
		tree->root = _removeNode(tree->root, val);
		tree->cnt--;
	}
}

/* remove val from AVL tree */
void removeAllAVLTree(struct AVLTree * tree, TYPE val)
{
	if(containsAVLTree(tree, val))
		tree->root = _removeAllNodes(tree, tree->root, val);
}


struct AVLnode * _removeAllNodes(struct AVLTree * tree, struct AVLnode * cur, TYPE val){
   struct AVLnode * temp = NULL;
   while(EQ(val, cur->val)){
      if(cur->right != 0){
         cur->val = _leftMost(cur->right);
         cur->right = _removeLeftmost(cur->right);
         tree->cnt--;
      } else {
         temp = cur->left;
         free(cur);
         tree->cnt--;
         cur = temp;
      }
   }
   if (cur){  
      if (LT(val, cur->val))
         cur->left = _removeAllNodes(tree,cur->left, val);
      else 
         cur->right = _removeAllNodes(tree,cur->right, val);
   }
   return _balance(cur);
  
}


