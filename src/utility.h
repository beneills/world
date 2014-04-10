#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define uniform_random() ((double)rand()/(double)RAND_MAX)
#define integer_uniform_random(n) ((unsigned int) (uniform_random() * n))
#define coordinates_to_index(m, x, y) ( m->width * y + y )
#define index_to_x(m, i) ( i % m->width )
#define index_to_y(m, i) ( i / m->width )

typedef enum { false, true } bool;

void* safe_malloc(size_t n, unsigned long line);
void* safe_calloc(size_t num, size_t size, unsigned long line);
void* safe_realloc(void* p, size_t n, unsigned long line);

#define SAFEMALLOC(n) safe_malloc(n, __LINE__)
#define SAFECALLOC(num, size) safe_calloc(num, size, __LINE__)
#define SAFEREALLOC(p, n) safe_realloc(p, n, __LINE__)
#endif
