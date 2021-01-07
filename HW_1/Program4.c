/* CS261- HW1 - Program4.c*/
/* Name: Iain Moncrief
 * Date: January 7, 2021
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

struct student{
	char initials[2];
	int score;
};

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


/* Proposition function that a is less than b, or that a should come before b alphabetically. */
int compare_equal_strings(char *a, char *b, int len) {
    return compare_equal_strings_recurse(a, b, len, len);
}

void swap(struct student* a, struct student* b) {
    struct student temp = *a;
    *a = *b;
    *b = temp;
}

void sort(struct student* students, int n){
     /*Sort n students based on their initials*/     
    int i, j, swapped;
    for (i = 0; i < n-1; i += 1) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j += 1) {
            
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

        students[i].score = rand() % 101;
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
