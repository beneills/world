#ifndef FAUNA_H_INCLUDED
#define FAUNA_H_INCLUDED

#include "map.h"

// maximum number of tries before giving up
#define FAUNA_GENERATE_MAX 10000

typedef struct fauna_s {
  unsigned int x, y; // position
  char* explored; // known places on map
  struct fauna_s* next;
} fauna;


fauna* fauna_new(unsigned int map_width, unsigned int map_height, unsigned int x, unsigned int y);
void fauna_free(fauna* f);
fauna* fauna_add(unsigned int map_width, unsigned int map_height, fauna* head, unsigned int x, unsigned int y);
void fauna_remove(fauna *head, fauna *f);
fauna* fauna_at(fauna* head, unsigned int x, unsigned int y);

fauna* fauna_generate(map* m, unsigned int n);
#endif

