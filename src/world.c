#include <stdlib.h>

#include "map.h"
#include "world.h"
#include "utility.h"

world* world_new(map* m) {
  world* w = (world *) SAFEMALLOC(sizeof(world));
  w->m = m;
  w->f = NULL;
  return w;
}

void world_free(world* w) {
  map_free(w->m);
  if (w->f != NULL) {
    fauna_free(w->f);
  }
  free(w);
}
