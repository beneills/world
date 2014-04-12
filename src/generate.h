#ifndef GENERATE_H_INCLUDED
#define GENERATE_H_INCLUDED

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "map.h"
#include "utility.h"

#define NULL_STRENGTH -10.0
#define VALID_STRENGTH(str) ((str) > NULL_STRENGTH/2)

typedef struct seed_s {
  int x, y;			/* we allow seeds off the map */
  double strength;		/* -1 strength signifies null seed */
  struct seed_s* next;
} seed;

typedef struct {		/* TODO use */
  bool (*meets_cutoff)(double);
  bool (*open_node)(int, int);
  double (*initial_strength)();
  double (*derived_strength)(double);
} generation_parameters;

extern const generation_parameters basic_params;
extern const generation_parameters null_params;

// public functions
void init_generator();
seed* seeds_add(seed* head,
		unsigned int x,
		unsigned int y,
		double strength);
void seeds_free(seed* head);
seed* seeds_generate(unsigned int width,
		     unsigned int height,
		     unsigned int n,
		     const generation_parameters* params);
void seeds_grow(seed* head, const generation_parameters* params);
bool seeds_contains(seed* head,
		    unsigned int x,
		    unsigned int y);
double initial_strength_unit();

#endif
