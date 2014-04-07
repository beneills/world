#include "utility.h"

// http://stackoverflow.com/questions/16297142/safe-malloc-realloc-wrapping-the-call-into-a-macro
// from Jim Balter
void* safe_malloc(size_t n, unsigned long line) {
    void* p = malloc(n);
    if (!p)
    {
        fprintf(stderr, "[%s:%u]Out of memory(%u bytes)\n",
                __FILE__, (unsigned int)line, (unsigned int)n);
        exit(EXIT_FAILURE);
    }
    return p;
}

