#ifndef GENERATE_FAUNA_H_INCLUDED
#define GENERATE_FAUNA_H_INCLUDED

#include "fauna.h"
#include "generate.h"
#include "map.h"
#include "world.h"

#define FAUNA_GENERATE_MAX 10000

fauna* fauna_generate(world* w, unsigned int n);
bool fauna_open_node(int x, int y);

#endif
