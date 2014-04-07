#include <stdlib.h>

#include "generate.h"
#include "map.h"
#include "world.h"

int main(int argc, char** argv) {
  seed_generator();

  printf("Generating map.\n");
  map *m = generate_random_map(100, 40, 15);

  char * output = map_render(m);
  printf(output);
  printf("\n");

  printf("Freeing map.\n");
  map_free(m);

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
