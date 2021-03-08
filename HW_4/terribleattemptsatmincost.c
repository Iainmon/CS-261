
#if 0
int findMinPath(struct AVLnode *root, TYPE *path)
{
	struct AVLnode *min_leaf, *curr;
	int i;
	int global_min; global_min = 99999999;
	_cfindMinPath(root, 0, &root->val, &global_min, &min_leaf);
	printf("min leaf: %d\n", min_leaf->val);
	printf("min cost  : %d\n", global_min);

	i = 0;
	curr = root;
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

	/* verify min cost */
	/*{
		int expected, found, j;
		found = 0;
		for (j = 0; j < i-1; j++)
		{
			found += abs(path[j] - path[j + 1]);
		}
		expected = min_cost_sum(root, root->val);
		printf("Expected: %d, Found: %d\n", expected, found);
	}*/
	return i;
}

typedef struct {
	struct AVLnode *node;
	int min_cost;
	struct AVLnode* walk[0xf];
	int i;
} Pair;
#define initpair(name) name.node=NULL;name.min_cost=0;

Pair getMin(struct AVLnode *root, int par_cost)
{
	Pair _cost, right_cost, left_cost;
	int right_min, left_min, cost, sub_tree_cost;
	if (root == NULL) {
		_cost.min_cost = par_cost;
		return _cost;
	}
	if (root->right == NULL && root->left == NULL) {
		assert(root->height == 0);
		cost = abs(par_cost - root->val);
		_cost.min_cost = cost;
		_cost.node = root;
		_cost.walk[0] = root;
		_cost.i = 1;
		return _cost;
	}

	cost = abs(par_cost - root->val);
	left_cost = getMin(root->left, root->val);
	right_cost = getMin(root->right, root->val);

	
	if (left_cost.min_cost < right_cost.min_cost) {
		/*_cost.min_cost = cost + left_cost.min_cost;
		_cost.node = left_cost.node;*/
		_cost = left_cost;
		_cost.min_cost += cost;
		_cost.walk[_cost.i] = root;
		_cost.i++;
	} else {
		/*_cost.min_cost = cost + right_cost.min_cost;
		_cost.node = right_cost.node;*/
		_cost = right_cost;
		_cost.min_cost += cost;
		_cost.walk[_cost.i] = root;
		_cost.i++;
	}

	return _cost;
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




int minPathRecurse(struct AVLnode *root, int par_cost, struct Deque *traversal)
{
	int left_min, right_min, cost, sub_tree_cost;
	struct Deque left_traversal, right_traversal;
	
	if (root == NULL) {
		return par_cost;
	}
	if (root->right == NULL && root->left == NULL) {
		cost = abs(par_cost - root->val);
		push_front(traversal, root);
		return cost;
	}
	left_traversal.front = NULL;
	right_traversal.front = NULL;
	left_traversal.back = NULL;
	right_traversal.back = NULL;
	left_traversal.size = 0;
	right_traversal.size = 0;
	/*left_traversal = init_dq();
	right_traversal = init_dq();*/

	cost = abs(par_cost - root->val);
	left_min = minPathRecurse(root->left, root->val, &left_traversal);
	right_min = minPathRecurse(root->right, root->val, &right_traversal);
	
	if (left_min < right_min) {
		traversal->front = left_traversal.front;
		traversal->back = left_traversal.back;
		traversal->size = left_traversal.size;
		sub_tree_cost = cost + left_min;
		/*(*traversal) = right_traversal;*/
		/* clear right traversal */
	} else {
		traversal->front = right_traversal.front;
		traversal->back = right_traversal.back;
		traversal->size = right_traversal.size;
		sub_tree_cost = cost + right_min;
		/*(*traversal) = right_traversal;*/
		/* clear left traversal */
	}

	push_front(traversal, root);

	/*sub_tree_cost = cost + min(left_min, right_min);*/
	return sub_tree_cost;
}
int FindMinPath2(struct AVLTree *tree, TYPE *path)
{
	int i,j, size, min_cost_test, parent_cost;
	Pair p;
	struct Deque *traversal;
	struct AVLnode *curr, *needle;
	struct List *lcurr;
	assert(tree);
	if (tree->root == NULL) return 0;

	p = getMin(tree->root, tree->root->val);
	printf("mincost: %d\n", p.min_cost);
	printf("mincostleaf: %d\n", p.node->val);
	assert(p.node->left == NULL);
	assert(p.node->right == NULL);
	
	/*min_cost_test = 0; parent_cost = tree->root->val;
	for (i = 0; i < p.i; i++) {
		path[p.i - i - 1] = p.walk[i]->val;
	}

	for (j = 0; j < i; j++) {
		min_cost_test += abs(parent_cost - path[j]);
		parent_cost = path[j];
	}
	printf("TEST: mincostfound: %d mincosttest: %d\n", p.min_cost, min_cost_test);

	return i;*/




	min_cost_test = 0;
	needle = p.node;
	assert(needle != NULL);
	parent_cost = tree->root->val;
	i = 0; curr = tree->root;
	while (1) {
		path[i] = curr->val;
		++i;
		min_cost_test += abs(parent_cost - curr->val);
		parent_cost = curr->val;
		if (curr->val == needle->val && curr->height == 0) {break;}
		if (needle->val <= curr->val) {
			curr = curr->left;
		} else {
			curr = curr->right;
		}
		if (curr == NULL) { printf("hitnull\n"); break;}
	}

	printf("TEST: mincostfound: %d mincosttest: %d\n", p.min_cost, min_cost_test);

	return i;

	traversal = init_dq();
	j = minPathRecurse(tree->root, tree->root->val, traversal);
	size = traversal->size;
	/*printf("dqsize: %d\n", size);
	printf("mincost: %d\n", j);*/

	/*lcurr = traversal->front;
	while (lcurr != NULL) {
		printf("dq val: %d \n", lcurr->value->val);
		lcurr = lcurr->next;
	}*/
	i = 0;
	while (i < size) /* (0 < traversal.size) */
	{
		curr = pop_back(traversal);
		path[size - i - 1] = curr->val;
		++i;
	}
	return i;
}
int FindMinPath1(struct AVLTree *tree, TYPE *path)
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
#endif