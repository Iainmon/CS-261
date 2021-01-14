/* CS261- HW1 - Program2.c*/
/* Name: Iain Moncrief
 * Date: January 6, 2021
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Defines the range of possible scores.
   The functions I implemented will generalize to any score range greater than 0 */
#define HIGHEST_SCORE 100
#define LOWEST_SCORE 0

#define STUDENT_COUNT 10

struct student{
	char initials[2];
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student* students_head = (struct student*)malloc(sizeof(struct student) * 10);

     /*return the pointer*/
     return students_head;
}


void generate(struct student* students){
     /*Generate random initials and scores for ten students.
	The two initial letters must be capital and must be between A and Z. 
	The scores must be between 0 and 100*/
     int i;
     for (i = 0; i < STUDENT_COUNT; i += 1) {
          students[i].initials[0] = 'A' + rand() % 26;
          students[i].initials[1] = 'A' + rand() % 26;

          students[i].score = rand() % (HIGHEST_SCORE - LOWEST_SCORE + 1) + LOWEST_SCORE;
     }
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              1. Initials  Score
              2. Initials  Score
              ...
              10. Initials Score*/
     int i;
     for (i = 0; i < STUDENT_COUNT; i += 1) {
          printf("%i. %s %i\n", i, students[i].initials, students[i].score);
     }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/

     int min, max; 
     /* Correctly initializes the max and min values for searching to work properly */
     min = HIGHEST_SCORE; max = LOWEST_SCORE;
     int total, i, curr;
     total = 0;
     for (i = 0; i < STUDENT_COUNT; i += 1) {
          /* Sums up the array, keeps track of the max and min values */
          curr = students[i].score;
          total += curr - LOWEST_SCORE;
          if (curr < min) {
               min = curr;
               continue;
          }
          if (curr > max) {
               max = curr;
          }
     }
     int average;
     average = (float)(total) / (float)(STUDENT_COUNT);

     printf("min: %d, max: %d, average: %d \n", min, max, average + LOWEST_SCORE);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
     if (stud == NULL) {
          return;
     }
     free(stud);
     stud = NULL;
}

int main(){
     /* Seeds the random function */
     srand(time(0));

     struct student* stud = NULL;
    
     /*call allocate*/
     stud = allocate();

     /*call generate*/
     generate(stud);

     /*call output*/
     output(stud);

     /*call summary*/
     summary(stud);

     /*call deallocate*/
     deallocate(stud);

     return 0;
}
