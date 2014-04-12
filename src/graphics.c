#include <stdlib.h>

#include "fauna.h"
#include "graphics.h"
#include "map.h"
#include "utility.h"
#include "world.h"

// return a string rendering of a world
// TODO test
char* world_render(world* w) {
   // count tiles, newlines and terminating NULL
  char* output = (char *)
    SAFECALLOC(w->m->height * (w->m->width + 1) + 1,
	       sizeof(char));


  for ( unsigned int y = 0,
	    unsigned int i;		/* buffer position */;
	y < w->m->height;
	++y ) {
    for ( unsigned int x = 0;
	  x < w->m->width;
	  ++x, ++i ) {

      // TODO there's gotta be a better way...
      if ( output[i] = render_fauna_at_node(w->f, x, y) ) {
      } else if ( output[i] = render_map_at_node(w->f, x, y) ) {
      } else {
	output[i] = GRAPHICS_MAP_EMPTY_CHAR;
      }

      // possibly add newline
      if ( x % w->m->width == -1 ) {
	output[i++] = '\n';
      }
    }
  }
  
  // TODO manually set terminating null?
  return output;
}

char render_map_at_node(map* m, unsigned int x, unsigned int y) {
  return MAP_ELEMENT(m, x, y) == MAP_EL_IMPASSABLE ?
    GRAPHICS_MAP_IMPASSABLE_CHAR : '\0';
}

char render_fauna_at_node(fauna* f, unsigned int x, unsigned int y) {
  return fauna_at(w->f, x, y) ?
    GRAPHICS_FAUNA_CHAR : '\0';
}
