# Leaky
<b>C / C++ Single-header library for memory menagement.</b>

# Example code
```c
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
    // Leaky will keep track of those values and, at the end of the program,
    // it's going to give you a raport of every allocation, every freeing,
    // how much memory you've allocated and freed and which variables cause the leaks!

    return 0;
}
```

# Description
Leaky is a C / C++ single-header library for menaging the memory of the program. It isn't implementing any idioms to make working with memory simpler (like for example, RAII idiom). It keeps track of allocating and freeing the memory, how much memory was allocated, freed and lost, and where the potential memory laks happend. The project was heavily inspired by the <b>`namantam1/memory-leak-detector`</b>: most of the original code was taken and redefined in the way that I think would work better and make the codebase cleaner and simpler. All the credits goes to this guy! 

# Informations
- <b>Original author:</b> This project was inspired by the [namantam1](https://github.com/namantam1). The repository used heavily in this project is [here](https://github.com/namantam1/memory-leak-detector).
- <b>Single-Header:</b> Leaky is a `single-header library`, so to make it work in your project you just need to drag-and-drop the `leaky.h` file.
- <b>#LEAKY_IMPLEMENTATION:</b> to make the Leaky work, you need to define the makro `LEAKY_IMPLEMENTATION` somewhere in your source files. It'll include the definitions of the functions used by Leaky. <b>THIS MAKRO MUST BE DEFINED ONLY ONCE. MULTIPLE DEFINITIONS OF THE `LEAKY_IMPLEMENTATION` WILL CAUSE THE PROBLEMS!</b>

# TODO:
- [ ] implement `realloc`.
- [ ] comment the codebase of the `leaky.h` file.
- [ ] write better example code.
- [ ] write tests.

# Licence
This project uses the [MIT](https://github.com/itsYakub/Leaky/blob/main/LICENSE) Licence.
