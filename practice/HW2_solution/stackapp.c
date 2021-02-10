/*	stackapp.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */
	char ch;
	char ts;
	int b=1;

	DynArr *stack;
	stack=newDynArr(5);


	if (s && strlen(s))
		while(1)
		{
			ch=nextChar(s);
			
			if(ch==0 || ch=='\0')
				break;

			if(ch=='(' || ch=='[' || ch=='{' )
				pushDynArr(stack,ch);
			else
			{
				if(!isEmptyDynArr(stack))
				{
					ts=topDynArr(stack);

					if(ch==')' && ts=='(')
						popDynArr(stack);
					else if(ch==')')
					{
						b=0;
						break;
					}
					else if(ch==']' && ts=='[')
						popDynArr(stack);
					else if (ch==']')
					{
						b=0;
						break;
					}
					else if(ch=='}' && ts=='{')
						popDynArr(stack);
					else if(ch=='}')
					{
						b=0;
						break;
					}
				}
				else if(ch=='}' || ch==')' || ch==']' )
				{
					b=0;
					break;
				}
			}

		}


	if( b && isEmptyDynArr(stack))
	{
		free(stack->data);
		free(stack);
		return 1;

	}

	free(stack->data);
	free(stack);
	return 0;
}

int main(int argc, char* argv[]){

	char* s=argv[1];	
	/*
	char s[]="()+x+r*{{{((--{{[()[]]}}))}}}";	
	*/

	int res;

	printf("Assignment 2\n");
	
	if(argc==2)
	{
		res = isBalanced(s);

		if (res)
			printf("The string %s is balanced\n",s);
		else 
			printf("The string %s is not balanced\n",s);
	}
	else
		printf("Please enter a string to be evaluated.\n");

	
	return 0;	
}

