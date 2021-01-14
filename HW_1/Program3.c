/* CS261- HW1 - Program3.c*/
/* Name: Iain Moncrief
 * Date: January 7, 2021
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Swap function for integers */
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void sort(int* number, int n){
    /*Sort the array of integers of length n*/     
    
    /* Bubble sort implementation */
    int i, j, swapped;
    for (i = 0; i < n-1; i += 1) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j += 1) {
            if (number[j] > number[j+1]) {
                swap(&number[j], &number[j+1]);
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

    /*Declare an integer n and assign it a value of 20.*/
    int n;
    n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
    int *numbers = (int*)malloc(sizeof(int) * n);
    
    /*Fill this array with random numbers, using rand().*/
    int i;
    for (i = 0; i < n; i += 1) {
        numbers[i] = rand();
    }

    /*Print the contents of the array.*/
    for (i = 0; i < n; i += 1) {
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }

    /*Pass this array along with n to the sort() function of part a.*/
    sort(numbers, n);

    /*Print the contents of the array.*/    
    for (i = 0; i < n; i += 1) {
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }

    return 0;
}
