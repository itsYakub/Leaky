#include <stdlib.h>

#define LEAKY_IMPLEMENTATION
#include "leaky.h"

int main(void){
    int* a = malloc(1024);

    float* b = malloc(16);
    char* c = malloc(128);

    free(a);
    free(b);
    //free(c);

    return 0;
}