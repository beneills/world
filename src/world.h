#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "fauna.h"
#include "map.h"

struct fauna_s; typedef struct fauna_s fauna; /* TODO forward declaration */

typedef unsigned int time;

typedef struct {
  map* m;
  fauna* f; // linked list of fauna
} world;

world* world_new();
void world_free(world* w);

#endif
