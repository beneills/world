#include "main.h"

int main(int argc, char** argv) {
  init_generator();		/* init PRNG */
  world* w = world_new();	/* create a world */
  /* w->m = generate_random_map_basic(30, 30, 5); /\* create random map *\/ */
  /* w->f = fauna_generate(w, 5);			 /\* generate some fauna *\/ */


  world_free(w);		/* free everything */
  return EXIT_SUCCESS;
}
