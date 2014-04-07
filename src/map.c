#include "map.h"
#include "utility.h"

map* map_new(unsigned int width, unsigned int height) {
  map* m = SAFEMALLOC(sizeof(map));
  m->width = width;
  m->height = height;
  m->data = SAFEMALLOC(height * width * sizeof(tile));
  return m;
}

void map_free(map* m) {
  if (m->data) {
    free(m->data);
  }
  free(m);
}
