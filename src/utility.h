#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum { false, true } bool;

void* safe_malloc(size_t n, unsigned long line);

#define SAFEMALLOC(n) safe_malloc(n, __LINE__)

#endif
