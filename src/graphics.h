#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "world.h"

#define GRAPHICS_MAP_EMPTY_CHAR ' '
#define GRAPHICS_MAP_IMPASSABLE_CHAR 0xdb /* block */
#define GRAPHICS_FAUNA_CHAR 'F'

char* world_render(world* w);
char render_map_at_node(map* m, unsigned int x, unsigned int y);
char render_fauna_at_node(fauna* f, unsigned int x, unsigned int y);

#endif

