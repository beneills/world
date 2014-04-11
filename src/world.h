#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "map.h"
#include "fauna.h"

// forward declaration TODO
struct fauna_s; typedef struct fauna_s fauna;

typedef unsigned int time;

typedef struct {
  map* m;
  fauna* f; // linked list of fauna
} world;

int main(int argc, char** argv);

world* world_new(map* m);
void world_free(world* w);

#endif
