#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define UNIFORM_RANDOM() ((double)rand()/(double)RAND_MAX)
#define INTEGER_UNIFORM_RANDOM(n) ((unsigned int) (UNIFORM_RANDOM() * (n))

#define SAFEMALLOC(n) safe_malloc((n), __LINE__)
#define SAFECALLOC(num, size) safe_calloc((num), (size), __LINE__)
#define SAFEREALLOC(p, n) safe_realloc((p), (n), __LINE__)

typedef enum { false, true } bool;

void* safe_malloc(size_t n, unsigned long line);
void* safe_calloc(size_t num, size_t size, unsigned long line);
void* safe_realloc(void* p, size_t n, unsigned long line);

#endif
