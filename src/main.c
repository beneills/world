#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fauna.h"
#include "generate.h"
#include "graphics.h"
#include "map.h"
#include "wander.h"
#include "world.h"


void reproduce(world* w) {
  fauna* f1;
  fauna* f2;
  fauna* child;
  fauna* first_child = NULL;
  for ( unsigned int x = 0; x < w->m->width; ++x ) {
    for ( unsigned int y = 0; y < w->m->height; ++y ) {
      if ( map_element(w->m, x, y) != MAP_EL_IMPASSABLE ) {
	// find all possible pairs of fauna
	for ( f1 = fauna_at(w->f, x, y);
	      f1 != NULL  && f1 != first_child;
	      f1 = fauna_at(f1->next, x, y) ) {
	  for ( f2 = fauna_at(f1->next, x, y);
		f2 != NULL && f2 != first_child;
		f2 = fauna_at(f2->next, x, y) ) {
	    printf("reproduce! (%f, %f)\n", f1->attr.reproducibility, f2->attr.reproducibility);
	    sleep(1);
	    // TODO element of chance
	    child = fauna_reproduce(w->m->width,
				    w->m->height,
				    w->f,
				    f1,
				    f2);
	    if ( first_child == NULL ) {
	      first_child = child;
	    }
	  }
	}
      }
    }
  }
}


void test() {
  printf("Generating map.\n");

  map* m = generate_random_map(4, 4, 0, NULL, NULL, NULL);
  world* w = world_new(m);

  w->f = fauna_generate(m, 2);

  char* output;

  // set random statuses
  for ( fauna* f = w->f;
	f != NULL;
	f = f->next ) {
    f->ws = wander_status_random();
  }

  // run at 1hz
  do {
    reproduce(w);
    output = world_render(w);
    printf("\e[1;1H\e[2J");
    puts(output);
    printf("\n");
    for ( fauna* f = w->f;
	  f != NULL;
	  f = f->next ) {
      printf("wander");
      fflush(stdout);
      wander_basic(w->m, f->ws, f);
      printf("...done\n");
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
