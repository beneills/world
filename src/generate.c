#include "generate.h"

// TODO delete
/* # define M_SQRT2	1.41421356237309504880	/\* sqrt(2) *\/ */
/* # define M_SQRT1_2	0.70710678118654752440	/\* 1/sqrt(2) *\/ */
/* # define M_PI		3.14159265358979323846	/\* pi *\/ */

// we try this many attempts per requested seed in seeds_generate
#define GENERATE_MAX_GENERATE_ATTEMPTS_MULTIPLIER 10

# define SQUARE(x) x*x

bool meets_cutoff_basic(double p);
bool open_node_basic(int x, int y);
double initial_strength_basic();
double derived_strength_basic(double parent_strength);

// call ONCE to initilize PRNG
void init_generator() {
  srand((unsigned) time(NULL));
}

// add a seed to end of list and return it
// if head == NULL, we start a new list seamlessly
// TODO test
seed* seeds_add(seed* head,
		unsigned int x,
		unsigned int y,
		double strength) {
  seed* s = (seed *) SAFEMALLOC(sizeof(seed));
  if ( head != NULL ) {
    for ( ; head->next != NULL; head = head->next )
      ;				/* intentionally blank */
    head->next = s;
  }

  return s;
}

void seeds_free(seed* head) {
  for ( seed* s = head; s != NULL;  head = s) {
    s = head->next;
    free(head);
  }
}

// generate initial seeds, guaranteed to be within map bounds
// may return fewer than n
seed* seeds_generate(unsigned int width,
		     unsigned int height,
		     unsigned int n,
		     generation_parameters* params) {
  seed *s, *head = NULL;
  for (unsigned int i = 0;
       i < n && i < GENERATE_MAX_GENERATE_ATTEMPTS_MULTIPLIER;
       ) {
    int x = (unsigned int) (uniform_random() * width);
    int y = (unsigned int) (uniform_random() * height);

    if ( (* params->open_node)(x, y) ) {
      s = seeds_add(head,
		    x,
		    y,
		    (* params->initial_strength)());
      ++i;
      if ( head == NULL ) { head = s; }
    }
  }

  return head;
}

// given an existing seed list, grow it according to params
void seeds_grow(seed* head, generation_parameters* params) {
  // while seed pool is non-empty, take a seed from the front and process it
  // strength < 0 is used for an empty map square, but stops it being repeatedly
  // considered
  for ( seed* s = head;
	s != NULL;
	s = s->next ) {
    // consider each of the 8 neighbours
    for ( int x = -1; d_x < 2; ++d_x ) {
      for ( int d_y = -1; d_y < 2; ++d_y ) {
	int x = s->x + d_x;
	int y = s->y + d_y;
	if ( !seeds_contains(s, x, y) ) {
	  double diagonal_multiplier = (d_x && d_y) ? 1.0 : M_SQRT2; /* cases diagonal and non-diagonal */
	  double strength = (* params->meets_cutoff)(uniform_random() *
						     s->strength *
						     diagonal_multiplier)
	    ? (* params->derived_strength)(s->strength) : -1.0;
	  seeds_add(s, x, y, strength); /* add to end of list */
	}
      }
    }
  }
}

bool seeds_contains(seed* head,
		    unsigned int x,
		    unsigned int y) {
  for ( ; head != NULL;  head = head->next) {
    if (head->x == x && head->y == y) {
      return true;
    }
  }
  return false;
}

double initial_strength_unit() {
  return 1.0;
}

bool meets_cutoff_basic(double p) {
  // TODO
  if (p > 0.1) {
    return true;
  } else {
    return false;
  }
}

bool open_node_basic(int x, int y) {
  return true;
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
