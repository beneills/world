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

extern const generation_parameters basic_params = {
  .meets_cutoff = &meets_cutoff_basic,
  .open_node = &open_node_basic,
  .initial_strength = &initial_strength_basic,
  .derived_strength = &derived_strength_basic
};

extern const generation_parameters null_params = {
  .meets_cutoff = NULL,
  .open_node = NULL,
  .initial_strength = &initial_strength_unit,
  .derived_strength = NULL
};

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
		       generation_parameters* params);
void seeds_grow(seed* head, generation_parameters* params);
bool seeds_contains(seed* head,
		    unsigned int x,
		    unsigned int y);
double initial_strength_unit();
#endif


// TODO move?
// maximum number of tries before giving up
#define FAUNA_GENERATE_MAX 10000
fauna* fauna_generate(world* w, unsigned int num);
