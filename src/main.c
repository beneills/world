#include <stdio.h>
#include <stdlib.h>

#include "generate.h"
#include "graphics.h"
#include "map.h"
#include "world.h"


int main(int argc, char** argv) {
  seed_generator();

  printf("Generating map.\n");

  map* m = generate_random_map(100, 40, 15, NULL, NULL, NULL);

  world* w = world_new(m);

  /* fauna *f = fauna_new(w->m->width, w->m->height, 0, 0); */
  /* fauna_add(w->m->width, w->m->height, f, 0, 1); */
  /* fauna_add(w->m->width, w->m->height, f, 2, 1); */

  w->f = fauna_generate(m, 10);

  char* output = world_render(w);

  puts(output);
  free(output);
  printf("\n");

  printf("Freeing world.\n");
  world_free(w);

  /* printf("Generating seeds.\n"); */
  /* seed* s = seeds_generate(5, 5, 10); */
  /* for ( seed* c = s; c != NULL;  c = c->next ) { */
  /*   printf("(%u, %u) = %f\n", c->x, c->y, c->strength); */
  /* } */
  /* printf("Freeing seeds.\n"); */

  /* if ( seeds_contains(s, 2, 2) ) { */
  /*     printf("Seed contains (2,2).\n"); */
  /* } */

  /* seeds_free(s);   */
  return EXIT_SUCCESS;
}
