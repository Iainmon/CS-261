#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>

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
}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  /*write this*/
}

struct hashLink* link_by_key(struct hashMap * ht, KeyType k) {
	assert(ht != NULL);
	hashLink* bkt;
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
	
}

int containsKey (struct hashMap * ht, KeyType k)
{  /*write this*/
	/* assert(ht != NULL);
	hashLink* bkt;
	bkt = ht->table[hash(k) % ht->tableSize];
	if (bkt == NULL) { return 0; }
	{
		hashLink* curr;
		curr = bkt;
		while (curr != NULL) {
			if (EQ(curr->key, k)) {
				return 1;
			}
			curr = curr->next;
		}
	}
	return 0; */
	assert(ht != NULL);
	struct hashLink* link;
	link = link_by_key(ht, k);
	if (link != NULL) { return 1; }
	return 0;
}

void removeKey (struct hashMap * ht, KeyType k)
{  /*write this?*/
	assert(ht != NULL);
	assert(ht->count > 0);
	struct hashLink* link;
	link = link_by_key(ht, k);
	if (link == NULL) { return; }
	{
		hashLink* bkt;
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
	}
}

int sizeMap (struct hashMap *ht)
{  /*write this*/
}

int capacityMap(struct hashMap *ht)
{  /*write this*/
}

int emptyBuckets(struct hashMap *ht)
{  /*write this*/
}

float tableLoad(struct hashMap *ht)
{  /*write this*/
}
