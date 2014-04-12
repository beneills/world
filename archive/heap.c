// Based on https://gist.github.com/martinkunev/1365481

#include "heap.h"
#include "utility.h"

#define CMP(a, b) ((a) < (b))

heap* heap_new() {
  heap* h = (heap *) SAFEMALLOC(sizeof(heap_type));
  h->allocated = HEAP_BASE_SIZE;
  h->count = 0;
  h->data = (heap_type *) SAFEMALLOC(HEAP_BASE_SIZE * sizeof(heap_type));
  return h;
}

void heap_free(heap* h) {
  free(h->data);
  free(h);
}

void heap_push(heap* h, heap_type datum) {
  // resize if necessary, with a doubling strategy
  if ( h->count == h->allocated ) {
    h->allocated <<= 1;
    h->data = SAFEREALLOC(h->data, sizeof(heap_type) * h->allocated);    
  }
  
  // and insert element
  unsigned int index, parent;
  for ( index = h->count++,
	  parent = (index - 1) >> 1;
	index &&
	  !CMP(h->data[parent], datum);
	index = parent,
	  parent = (index - 1) >> 1)
    {
      h->data[index] = h->data[parent];
    }
  h->data[index] = datum;
}

void heap_print(heap* h) {
  for ( unsigned int i = 0; i < h->count; ++i ) {
    printf("%u ", h->data[i]);
  }
  printf("\n");
}
