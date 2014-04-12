#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "fauna.h"
#include "map.h"
#include "types.h"


world* world_new();
void world_free(world* w);

#endif
