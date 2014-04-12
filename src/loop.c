#include "loop.h"

void loop(world* w) {
  char* output;

  do {				/* run at 1hz */
    clear_screen();
    output = world_render(w);
    puts(output); printf("\n");

    for ( fauna* f = w->f;	/* wander */
	  f != NULL;
	  f = f->next ) {
      wander_basic(w, f);
    }

    sleep(1);			/* regulate framerate */
  } while ( true );

  free(output);
}
