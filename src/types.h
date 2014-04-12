#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

typedef unsigned int epoch;

typedef struct node_s {
  unsigned int x, y;
} node;

typedef struct {
  unsigned int width;
  unsigned int height;
  char* data;
} map;

typedef struct wander_status_s {
  double angle;			/* radians, in [0, 2pi) */
} wander_status;

typedef struct {
  double reproducibility;
} gene_attributes;

typedef struct {
  wander_status* wander;
} status_attributes;

typedef struct fauna_s {
  // base members
  node position;
  epoch born;
  char* explored; // known places on map

  // module members
  gene_attributes* genes;
  status_attributes* status;

  // data structure
  struct fauna_s* next;
} fauna;


typedef struct world_s {
  map* m;
  fauna* f; // linked list of fauna
} world;

#endif
