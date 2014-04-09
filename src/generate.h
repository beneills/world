#ifndef GENERATE_H_INCLUDED
#define GENERATE_H_INCLUDED

#include "map.h"
#include "utility.h"

#define MEETS_CUTOFF_DEFAULT &meets_cutoff_basic
#define INITIAL_STRENGTH_DEFAULT &initial_strength_basic
#define DERIVED_STRENGTH_DEFAULT &derived_strength_basic


// linked list of seeds
typedef struct seed_s {
  unsigned int x;
  unsigned int y;
  double strength;
  struct seed_s* next;
} seed;

// TODO use
typedef struct {
  bool (*meets_cutoff)(double);
  double (*initial_strength)();
  double (*derived_strength)(double);
} map_generation_parameters;

void seed_generator();
seed* seeds_generate(unsigned int width,
		       unsigned int height,
		       unsigned int n,
		       double (*initial_strength)());
seed* seeds_free(seed* s);
void seeds_add(seed* s,
	       unsigned int x,
	       unsigned int y,
	       double strength);
bool seeds_contains(seed* s,
		    unsigned int x,
		    unsigned int y);
bool meets_cutoff_basic(double p);
double initial_strength_basic();
double derived_strength_basic(double parent_strength);

map* generate_random_map(unsigned int width,
			   unsigned int height,
			   unsigned int seeds,
			   bool (*meets_cutoff)(double),
			   double (*initial_strength)(),
			   double (*derived_strength)(double));

#endif

