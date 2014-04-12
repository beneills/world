#ifndef GENERATE_MAP_H_INCLUDED
#define GENERATE_MAP_H_INCLUDED

#include "generate.h"
#include "map.h"

map* generate_random_map(unsigned int width,
			 unsigned int height,
			 unsigned int seeds,
			 const generation_parameters* params);
map* generate_random_map_basic(unsigned int width,
			       unsigned int height,
			       unsigned int seeds);

#endif
