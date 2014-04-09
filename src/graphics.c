#include "fauna.h"
#include "graphics.h"
#include "map.h"
#include "utility.h"


char* world_render(world* w) {
  map* m = w->m;

  // count tiles, newlines and terminating NULL
  int bytes = m->height * (m->width + 1) + 1;
  char* output = (char *) SAFEMALLOC(bytes * sizeof(char));
  memset(output, '\0', bytes);
  int j = 0; // output string position
  for ( unsigned int i = 0; i < m->height * m->width; ++i, ++j ) {
    if (i > 0 && index_to_x(m, i) == 0) {
      output[j] = '\n';
      ++j;
    }
    if ( fauna_at(w->f, index_to_x(m, i), index_to_y(m, i)) ) {
      output[j] = 'F';
    } else {
      output[j] = m->data[i] == MAP_EL_IMPASSABLE ? 'X' : ' ';
    }
  }
  output[bytes-1] = '\0';
  return output;
}
