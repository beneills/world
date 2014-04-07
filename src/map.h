#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#define MAP_EL_EMPTY 0x00
#define MAP_EL_IMPASSABLE 0x01


#define map_element(m, x, y) m->data[y*m->width + x]

typedef char tile;

typedef struct {
  unsigned int width;
  unsigned int height;
  tile* data;
} map;

map* map_new(unsigned int width, unsigned int height);
void map_free(map* m);

#endif
