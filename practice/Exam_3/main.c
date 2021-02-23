#include "tree.c"


#define add(a) ;bst->root=insert_bst(bst->root,a);

int main() {
    struct BSTree* bst;
    bst = malloc(sizeof(struct BSTree));

    /*int i;
    for (i = 0; i < 10; i++) {
        int v = (i % 2 == 0) ? 10+i : 10-i;
        bst->root = insert_bst(bst->root, v);
    }*/

    add(4); add(2); add(3); add(1); add(0); add(6); add(5);
    
    
    pre_order_print(bst->root);
    printf("----- left branch:\n");
    left_trav(bst->root);
    printf("----- BFS: \n");
    bfs(bst,2);
    printf("----- DFS: \n");
    dfs(bst, 2);

    return 0;
}