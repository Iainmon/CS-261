#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers separated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file); /* prototype */

/****************************************/

int main (int argc, const char * argv[]) {
    /*Write this function*/
	FILE *fp;
	struct hashMap* ht;
	fp = fopen("./input.txt", "r");
	assert(fp != NULL);
	ht = (struct hashMap*)malloc(sizeof(struct hashMap));
	initMap(ht, 7);
	while (1) {
		char* word;
		word = getWord(fp);
		if (word == NULL) {
			fclose(fp);
			break;
		}
		printf("Word: %s\n", word);
		{
			struct hashLink* pair;
			pair = link_by_key(ht, word);
			if (pair == NULL) {
				insertMap(ht, word, 0);
			} else {
				pair->value++;
			}
		}
	}

	{
		int i; i = 0;
		while (i < ht->tableSize)
		{
			struct hashLink* curr;
			curr = ht->table[i];
			while (curr != NULL)
			{
				printf("%s:%d\n", curr->key, curr->value);
				curr = curr->next;
			}
			++i;
		}
	}
}




char* getWord(FILE *file)
{
	
	int length = 0;
	int maxLength = 16;
	char character;
    
	char* word = (char*)malloc(sizeof(char) * maxLength);
	assert(word != NULL);
    
	while( (character = fgetc(file)) != EOF)
	{
		if((length+1) > maxLength)
		{
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);
		}
		if((character >= '0' && character <= '9') || /*is a number*/
		   (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
		   (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
		   character == 39) /*or is an apostrophy*/
		{
			word[length] = character;
			length++;
		}
		else if(length > 0)
			break;
	}
    
	if(length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}

