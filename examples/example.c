#include <stdlib.h>

#define LEAKY_IMPLEMENTATION
#include "leaky.h"

int main(void){
    // This will cause a memory leak of size: 4 bytes
    int* integer = malloc(sizeof(int));
    *integer = 8;

    // This will cause a memory leak of size: 4 * 2 bytes...
    float* floatingValue = calloc(sizeof(float), 2);
    floatingValue[0] = 3.14159f;
    floatingValue[1] = 0.123f;

    // ..unless You call the free() function!
    free(floatingValue);

    // This will cause a memory leak of size: 8 * 1 bytes
    char* sentance = malloc(8 * sizeof(char));
    sentance = "Hello, world!";

    // At the end of the program we have two memory leaks:
    //      > 1. *integer at line 8;
    //      > 2. *sentance at line 20;
    // Leaky will keep track of those values and, at the end of the program, it's going to give you a raport of every allocation, every freeing, how much memory you've allocated and freed and which variables cause the leaks!

    return 0;
}