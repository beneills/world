#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
// TODO why can't I get this from math.h?
# define M_SQRT2	1.41421356237309504880	/* sqrt(2) */
# define M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */
# define M_PI		3.14159265358979323846	/* pi */

# define SQUARE(x) x*x

#include "generate.h"
#include "utility.h"


void seed_generator() {
  srand((unsigned) time(NULL));
}

seed* seeds_generate(unsigned int width,
		     unsigned int height,
		     unsigned int n,
		     double (*initial_strength)()) {
  seed *c;
  seed *h = NULL;
  for (int i = 0; i < n; ++i) {
    // TODO use seeds_add
    c = (seed *) SAFEMALLOC(sizeof(seed));

    // TODO this possibly fails on edge case (literally)
    c->x = (unsigned int) (uniform_random() * width);
    c->y = (unsigned int) (uniform_random() * height);

    c->strength = (* initial_strength)();
    c->next = h;
    h = c;
  }

  return h;
}

seed* seeds_free(seed* s) {
  for ( seed* c = s; c != NULL;  s = c) {
    c = s->next;
    free(s);
  }
}

void seeds_add(seed* s,
	       unsigned int x,
	       unsigned int y,
	       double strength) {
  for ( ; s->next != NULL;  s = s->next) {}

  s->next = (seed *) SAFEMALLOC(sizeof(seed));
  s->next->x = x;
  s->next->y = y;
  s->next->strength = strength;
  s->next->next = NULL;
}

bool seeds_contains(seed* s,
		    unsigned int x,
		    unsigned int y) {
  for ( ; s != NULL;  s = s->next) {
    if (s->x == x && s->y == y) {
      return true;
    }
  }
  return false;
}

bool meets_cutoff_basic(double p) {
  // TODO
  if (p > 0.1) {
    return true;
  } else {
    return false;
  }
}

// used for the very first (parentless) seeds
double initial_strength_basic() {
  return cos(uniform_random()); // TODO factor of pi?
}


double derived_strength_basic(double parent_strength) {
  // TODO
  // return parent_strength * 0.7;
  return SQUARE(cos(parent_strength * M_PI / 2.0));
}

map* generate_random_map(unsigned int width,
			 unsigned int height,
			 unsigned int seeds,
			 bool (*meets_cutoff)(double),
			 double (*initial_strength)(),
			 double (*derived_strength)(double)) {
  // possibly use defaults
  if ( meets_cutoff == NULL ) {
    meets_cutoff = MEETS_CUTOFF_DEFAULT;
  }
  if ( initial_strength == NULL ) {
    initial_strength = INITIAL_STRENGTH_DEFAULT;
  }
  if ( derived_strength == NULL ) {
    derived_strength = DERIVED_STRENGTH_DEFAULT;
  }


  map* m = map_new(width, height);
  seed* s = seeds_generate(width, height, seeds, initial_strength);

  // while seed pool is non-empty, take a seed from the front and process it
  // strength < 0 is used for an empty map square, but stops it being repeatedly
  // considered
  for ( seed* c = s;
	c != NULL;
	c = c->next ) {
    // possibly add the seed to the map
    if (c->strength > -1) {
      map_element(m, c->x, c->y) = MAP_EL_IMPASSABLE;
    }

    // consider each of the 8 neighbours
    for ( int d_x = -1; d_x < 2; ++d_x ) {
      for ( int d_y = -1; d_y < 2; ++d_y ) {
	int x = c->x + d_x;
	int y = c->y + d_y;
	// check that we're still on the map,
	// but not already in the seed list
	if ( !(d_x == 0 && d_y == 0) &&
	     x >= 0 && x < width &&
	     y >= 0 && y < height &&
	     !seeds_contains(s, x, y) ) {
	  // cases diagonal and non-diagonal
	  double diagonal_multiplier = (d_x && d_y) ? 1.0 : M_SQRT2;
	  double strength = (* meets_cutoff)(uniform_random() *
					     c->strength *
					     diagonal_multiplier)
	    ? (* derived_strength)(c->strength) : -1.0;
	  // add to pool
	  seeds_add(c, (unsigned int) x, (unsigned int) y, strength);
	}
      }
    }
  }
  seeds_free(s);
  return m;
}
