#include "utility.h"
#include "graphics.h"


char* map_render(map* m) {
  // count tiles, newlines and terminating NULL
  char* output = SAFEMALLOC((m->height * (m->width + 1) + 1) * sizeof(char));
  int j = 0; // output string position
  for ( unsigned int i = 0; i < m->height * m->width; ++i, ++j ) {
    if (i > 0 && i % m->width == 0) {
      output[j] = '\n';
      ++j;
    }
    output[j] = m->data[i] == MAP_EL_IMPASSABLE ? 'X' : ' ';
  }
  return output;
}
