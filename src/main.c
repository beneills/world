#include "main.h"

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

}


int main(int argc, char** argv) {
  init_generator();		/* init PRNG */
  world* w = world_new();	/* create a world */
  w->map = generate_random_map_basic(30, 30, 5); /* create random map */
  w->f = fauna_generate(w, 5);			 /* generate some fauna */


  world_free(w);		/* free everything */
  return EXIT_SUCCESS;
}
