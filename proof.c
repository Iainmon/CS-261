void f(int n) {
   while (n > 1)
      if (n % 2 == 0)
          n = n / 2;
      else
          n = 3 * n + 1;
}
#include <stdio.h>
int main () {int i; i = 0; while (1) {printf("%d\n",i); f(i); ++i;} return 0;}