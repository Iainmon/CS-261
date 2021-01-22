#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define sat 0b11111111111111111111111111111111

unsigned char* crypt(unsigned char* data, int n) {
    assert(n > 0);
    char* coded;
    coded = (unsigned char*)malloc(sizeof(unsigned char) * n);
    assert(coded != NULL);
    int i; i = 0;
    unsigned char last; last = 0;
    while (i < n) {
        coded[i] = last ^ data[i];
        last = data[i];
        ++i;
    }
    return coded;
}

int main() {
    unsigned char* data = "Hello my name is Iain.";
    int n = strlen(data);
    unsigned char* coded = crypt(data, n);
    printf("%s\n", data);
    printf("%s\n", coded);
    return 1;
}