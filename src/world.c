#include <stdlib.h>

#include "map.h"
#include "world.h"
#include "utility.h"

// allocate a new world object
world* world_new() {
  world* w = (world *) SAFECALLOC(1, sizeof(world));
  w->m = NULL;
  w->f = NULL;
  return w;
}

// free a world and its contents
void world_free(world* w) {
  map_free(w->m);
  fauna_free(w->f);
  free(w);
}
