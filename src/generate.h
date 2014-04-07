#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "map.h"
#include "utility.h"

// linked list of seeds
typedef struct seed_s {
  unsigned int x;
  unsigned int y;
  double strength;
  struct seed_s* next;
} seed;

void seed_generator();
seed* seeds_generate(unsigned int width,
		     unsigned int height,
		     unsigned int n);
seed* seeds_free(seed* s);
void seeds_add(seed* s,
	       unsigned int x,
	       unsigned int y,
	       double strength);
bool seeds_contains(seed* s,
		    unsigned int x,
		    unsigned int y);
bool meets_cutoff(double p);
double initial_strength();
double derived_strength(double parent_strength);
map* generate_random_map(unsigned int width,
			 unsigned int height,
			   unsigned int seeds);
#endif

