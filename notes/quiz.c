

void _removeDLink (struct dlist *bag, struct dlink *lnk) {
    assert(bag && lnk);
    assert(bag->size > 0);
    lnk->next->prev = lnk->prev;
    lnk->prev->next = lnk->next;
    lnk->next = NULL;
    lnk->prev = NULL;
    free(lnk);
    bag->size--;
}