#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "map.h"
#include "fauna.h"

typedef struct {
  map* m;
  fauna* f; // linked list of fauna
} world;

int main(int argc, char** argv);

world* world_new(map* m);
void world_free(world* w);

#endif
