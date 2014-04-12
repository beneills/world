#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "types.h"

#define MAP_EL_EMPTY 0x00
#define MAP_EL_IMPASSABLE 0x01

#define NODE_EQ(n1, n2) ((n1).x == (n2).x && (n1).y == (n2).y)
#define NODE(x, y) ({.x = (x), .y = (y)})
#define MAP_ELEMENT(m, x, y) m->data[y*m->width + x]
#define MAP_NODE_VALID(m, x, y) (x) >= 0 && \
    (x) < m->width && \
    (y) >= 0 && \
    (y) < m->height

map* map_new(unsigned int width, unsigned int height);
void map_free(map* m);

#endif
