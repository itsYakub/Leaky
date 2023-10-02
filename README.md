# Leaky
<b>C / C++ Single-header library for memory menagement.</b>

# Example code
```c
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
```

# Description
Leaky is a lightweight C/C++ single-header library designed for memory management in your programs. Unlike some libraries that introduce complex memory management idioms (e.g., RAII), Leaky takes a more straightforward approach. It diligently tracks memory allocation and deallocation, monitors memory consumption, and helps you identify potential memory leaks in your code.

This project draws significant inspiration from [namantam1's memory-leak-detector](https://github.com/namantam1/memory-leak-detector). While the original code served as a foundation, it has been redefined and refined to improve functionality, codebase cleanliness, and simplicity. Credit goes to the original author for their valuable work.

# Information
- **Original Author:** Leaky was inspired by the work of [namantam1](https://github.com/namantam1), and it leverages their repository, which can be found [here](https://github.com/namantam1/memory-leak-detector).
- **Single-Header:** Leaky is designed as a `single-header library`, which means you can effortlessly integrate it into your project by simply including the `leaky.h` file.
- **#LEAKY_IMPLEMENTATION:** To make Leaky functional in your project, you need to define the `LEAKY_IMPLEMENTATION` macro once within your source files. This macro includes the necessary function definitions used by Leaky. **Please note that defining `LEAKY_IMPLEMENTATION` multiple times can lead to issues, so ensure it's defined only once.**

# TODO:
- [X] implement `realloc`.
- [ ] comment the codebase of the `leaky.h` file.
- [ ] write better example code.
- [ ] write tests.

# Licence
This project uses the [MIT](https://github.com/itsYakub/Leaky/blob/main/LICENSE) Licence.
