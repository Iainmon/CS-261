/* CS261- HW1 - Program4.c*/
/* Name: Iain Moncrief
 * Date: January 7, 2021
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Defines the range of possible scores.
   The functions I implemented will generalize to any score range greater than 0 */
#define HIGHEST_SCORE 100
#define LOWEST_SCORE 0

struct student{
	char initials[2];
	int score;
};

/* Recursive string comparison.
    -1 if strings are equal
    1 if string a should come before b alphabetically
    0 if string a should come after b alphabetically

Defined more readably in haskell:

type Swapper = (Char,Char) -> (Char,Char)
swap (a,b) = (b,a)
noSwap = id
alphOrder :: [Char] -> [Char] -> Maybe Swapper
alphOrder _ [] = Nothing
alphOrder [] _ = Nothing
alphOrder (x:xs) (y:ys)
    | x == y     = alphOrder xs ys
    | x > y      = Just swap
    | otherwise  = Just noSwap
*/
int compare_equal_strings_recurse(char *a, char *b, int len, int n) {
    if (len - n >= len) {
        return -1;
    }
    if (a[len - n] == b[len - n]) {
        return compare_equal_strings_recurse(a, b, len, n-1);
    }
    if (a[len - n] < b[len - n]) {
        return 1;
    }
    return 0;
}

/* Proposition function that a is less than b, or that a should come before b alphabetically.
 Just wraps compare_equal_strings_recurse without the extra recursive parameter. */
int compare_equal_strings(char *a, char *b, int len) {
    return compare_equal_strings_recurse(a, b, len, len);
}

/* Swap function for struct student */
void swap(struct student* a, struct student* b) {
    struct student temp = *a;
    *a = *b;
    *b = temp;
}

void sort(struct student* students, int n){
     /*Sort n students based on their initials*/     
    
    /* Bubble sort implamentation. This already handles the case where n = 0 */
    int i, j, swapped;
    for (i = 0; i < n-1; i += 1) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j += 1) {
            /* Flips elements if element i+1 should come before element i */
            if (compare_equal_strings(students[j+1].initials, students[j].initials, 2) > 0) {
                swap(&students[j], &students[j+1]);
                swapped = 1;
            }
        }
        if (swapped < 1) {
            break;
        }
    }
}

int main(){
    /* Seeds the random function */
    srand(time(0));
    
    /*Declare an integer n and assign it a value.*/
    int n;
    n = 20;

    /*Allocate memory for n students using malloc.*/
    struct student* students = (struct student*)malloc(sizeof(struct student) * n);

    /*Generate random IDs and scores for the n students, using rand().*/
    int i;
    for (i = 0; i < n; i += 1) {
        students[i].initials[0] = 'A' + rand() % 26;
        students[i].initials[1] = 'A' + rand() % 26;

        students[i].score = rand() % (HIGHEST_SCORE - LOWEST_SCORE + 1) + LOWEST_SCORE;
    }

    /*Print the contents of the array of n students.*/
    for (i = 0; i < n; i += 1) {
        printf("%i. %s %i\n", i, students[i].initials, students[i].score);
    }

    /*Pass this array along with n to the sort() function*/
    sort(students, n);

    /*Print the contents of the array of n students.*/
    for (i = 0; i < n; i += 1) {
        printf("%i. %s %i\n", i, students[i].initials, students[i].score);
    }

    return 0;
}
