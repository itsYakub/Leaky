#include <stdlib.h>

#define LEAKY_IMPLEMENTATION
#include "leaky.h"

int main(void){
    // This will cause a memory leak of size: sizeof(int) bytes
    int* integer = malloc(sizeof(int));
    *integer = 8;

    // This will cause a memory leak of size: 2 * sizeof(float) bytes...
    float* floatingValue = calloc(sizeof(float), 2);
    floatingValue[0] = 3.14159f;
    floatingValue[1] = 0.123f;

    // ..unless You call the free() function!
    free(floatingValue);

    // This call is allocating the memory of size: 8 * sizeof(char) bytes...
    char* sentance = malloc(8 * sizeof(char));

    // ...which is the reallocated with the size: 16 * sizeof(char). The reallocation will cause a memory leak, bacause the previous char* was freed during the process
    char* newSentance = realloc(sentance, 16 * sizeof(char));

    // At the end of the program we have two memory leaks:
    //      > 1. *integer at line 8;
    //      > 2. *newSentance at line 23;
    // Leaky will keep track of those values and, at the end of the program, it's going to give you a raport of every allocation, every freeing, how much memory you've allocated and freed and which variables cause the leaks!

    return 0;
}