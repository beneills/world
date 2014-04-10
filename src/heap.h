#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include <stddef.h>
#include <stdlib.h>

#define HEAP_BASE_SIZE 4
#define HEAP_PRINT_MAX 1024

typedef int heap_type;

typedef struct {
  unsigned int allocated;
  unsigned int count;
  size_t data_size; // size of each datum
  heap_type* data;
} heap;

heap* heap_new();
void heap_free(heap* h);
void heap_push(heap* h, heap_type datum);
void heap_print(heap* h);

#endif
