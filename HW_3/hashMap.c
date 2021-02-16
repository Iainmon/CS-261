#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>
#include <assert.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

#ifdef HASHING_FUNCTION
#if HASHING_FUNCTION
#define hash(x) stringHash1(x)
#else
#define hash(x) stringHash2(x)
#endif
#else
#define hash(x) stringHash1(x)
#endif

struct hashLink* link_by_key(struct hashMap * ht, KeyType k);

void initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht)
{  /*write this*/
	int i; i = 0;
	assert(ht != NULL);
	while (i < ht->tableSize)
	{
		hashLink* curr;
		curr = ht->table[i];
		while (curr != NULL)
		{
			hashLink* prev;
			prev = curr;
			curr = curr->next;
			free(prev);
		}
	}
	free(ht);
}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  /*write this*/
	int bkt;
	hashLink* pair;
	assert(ht != NULL);
	pair = link_by_key(ht, k);
	if (pair != NULL) {
		pair->value = v;
		return;
	}
	pair = (struct hashLink*)malloc(sizeof(struct hashLink));
	assert(pair != NULL);
	bkt = hash(k) % ht->tableSize;
	pair->key = k;
	pair->value = v;
	pair->next = ht->table[bkt];
	ht->table[bkt] = pair;
	ht->count++;
}

hashLink* link_by_key(struct hashMap * ht, KeyType k) {
	hashLink* bkt;
	assert(ht != NULL);
	bkt = ht->table[hash(k) % ht->tableSize];
	if (bkt == NULL) { return NULL; }
	{
		hashLink* curr;
		curr = bkt;
		while (curr != NULL) {
			if (EQ(curr->key, k)) {
				return curr;
			}
			curr = curr->next;
		}
	}
	return NULL;
}

ValueType* atMap (struct hashMap * ht, KeyType k)
{ /*write this?*/
	hashLink* lnk;
	assert(ht != NULL);
	lnk = link_by_key(ht, k);
	if (lnk == NULL) { return NULL; }
	return &lnk->value;
}

int containsKey (struct hashMap * ht, KeyType k)
{  /*write this*/
	hashLink* lnk;
	assert(ht != NULL);
	lnk = link_by_key(ht, k);
	if (lnk != NULL) { return 1; }
	return 0;
}

void removeKey (struct hashMap * ht, KeyType k)
{  /*write this?*/
	hashLink* lnk;
	assert(ht != NULL);
	assert(ht->count > 0);
	{
		lnk = link_by_key(ht, k);
		if (lnk == NULL) { return; }
	}
	{
		hashLink* bkt;
		int idx;
		idx = hash(k) % ht->tableSize;
		bkt = ht->table[idx];
		if (bkt == NULL) { return; }
		if (bkt == lnk)
		{
			ht->table[idx] = lnk->next;
			free(lnk);
			ht->count--;
			return;
		}
		{
			hashLink* curr;
			curr = bkt;
			while (curr != NULL)
			{
				if (curr->next == lnk)
				{
					curr->next = lnk->next;
					free(lnk);
					ht->count--;
					return;
				}
				curr = curr->next;
			}
		}
	}
}

int sizeMap (struct hashMap *ht)
{  /*write this*/
	assert(ht != NULL);
	return ht->count;
}

int capacityMap(struct hashMap *ht)
{  /*write this*/
	assert(ht != NULL);
	return ht->tableSize;
}

int emptyBuckets(struct hashMap *ht)
{  /*write this*/
	int i;
	int count;
	i = 0;
	count = 0;
	while (i < ht->tableSize) {
		if (ht->table[i] == NULL) { ++count; }
		++i;
	}
	return count;
}

float tableLoad(struct hashMap *ht)
{  /*write this*/
	return (float)ht->count / (float)ht->tableSize;
}
