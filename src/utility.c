#include <stdlib.h>

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

void* safe_calloc(size_t num, size_t size, unsigned long line) {
  void* p = calloc(num, size);
  if (!p)
    {
      fprintf(stderr, "[%s:%u]Out of memory(%u bytes)\n",
	      __FILE__, (unsigned int)line, (unsigned int)(num*size));
      exit(EXIT_FAILURE);
    }
  return p;
}

void* safe_realloc(void* p, size_t n, unsigned long line) {
  p = realloc(p, n);
  if (!p)
    {
      fprintf(stderr, "[%s:%u]Out of memory(%u bytes)\n",
	      __FILE__, (unsigned int)line, (unsigned int)n);
      exit(EXIT_FAILURE);
    }
  return p;
}
