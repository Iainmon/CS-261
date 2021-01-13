/* CS261- HW1 - Program1.c*/
/* Name: Iain Moncrief
 * Date: January 6, 2021
 * Solution description: Filled in the appropriate code, and used the modulo (%) operator to get a random int within a range.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
    /* Increment a */
    *a += 1;

    /* Decrement  b */
    *b -= 1;

    /* Assign a-b to c */
    c = (*a)-(*b);

    /* Return c */
    return c;
}

#define random_inclusive(from) rand()%(from+1)
#define RANDOM_UPPER_BOUND 10
#define prelude srand(time(0));

int main(){
    prelude;

    /* Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    int x, y, z;
    x = random_inclusive(RANDOM_UPPER_BOUND);
    y = random_inclusive(RANDOM_UPPER_BOUND);
    z = random_inclusive(RANDOM_UPPER_BOUND);

    /* Print the values of x, y and z */
    printf("x: %i, y: %i, z: %i\n", x, y, z);

    /* Call foo() appropriately, passing x,y,z as parameters */
    int w = foo(&x, &y, z);

    /* Print the values of x, y and z */
    printf("x: %i, y: %i, z: %i\n", x, y, z);

    /* Print the value returned by foo */
    printf("foo(x, y, z): %i\n", w);

    /* Is the return value different than the value of z?  Why? */
    return 0;
}