#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "utility.h"

map* map_new(unsigned int width, unsigned int height) {
  map* m = (map *) SAFEMALLOC(sizeof(map));
  m->width = width;
  m->height = height;
  m->data = (char *) SAFECALLOC(height * width, sizeof(char)); /* NOTE we rely on MAP_EL_EMPTY == '\0' */
  return m;
}

void map_free(map* m) {
  free(m->data);
  free(m);
}
