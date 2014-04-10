#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "generate.h"
#include "graphics.h"
#include "map.h"
#include "wander.h"
#include "world.h"


void test() {
  printf("Generating map.\n");

  map* m = generate_random_map(10, 10, 1, NULL, NULL, NULL);
  world* w = world_new(m);

  w->f = fauna_generate(m, 1);

  char* output;

  // set random statuses
  for ( fauna* f = w->f;
	f != NULL;
	f = f->next ) {
    f->ws = wander_status_random();
  }

  // run at 1hz
  do {
    output = world_render(w);
    printf("\e[1;1H\e[2J");
    puts(output);
    printf("\n");
    for ( fauna* f = w->f;
	  f != NULL;
	  f = f->next ) {
      wander_basic(w->m, f->ws, f);
    }
    sleep(1);
  } while ( true );

  free(output);


  printf("Freeing world.\n");
  world_free(w);
}


int main(int argc, char** argv) {
  seed_generator();
  test();
  return EXIT_SUCCESS;
}
