#include "generate_map.h"

map* generate_random_map(unsigned int width,
			 unsigned int height,
			 unsigned int seeds,
			 generation_parameters* params) {
  map* m = map_new(width, height);
  seed* head = seeds_generate(width, height, seeds, params);

  seeds_grow(s, params);

  for ( seed* s = head;
	s != NULL;
	s = s->next ) {
    if ( VALID_STRENGTH(s->strength) &&
	 MAP_NODE_VALID(m, s->x, s->y ) ) {
      MAP_ELEMENT(m, s->x, s->y) = MAP_EL_IMPASSABLE;
    }
  }

  seeds_free(head);

  return m;
}

map* generate_random_map_basic(unsigned int width,
			       unsigned int height,
			       unsigned int seeds) {
  return generate_random_map(width,
			     height,
			     seeds,
			     &basic_params);
}
