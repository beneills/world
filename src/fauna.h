#ifndef FAUNA_H_INCLUDED
#define FAUNA_H_INCLUDED

#include "wander.h"
#include "world.h"

typedef struct {
  double reproducibility;
} gene_attributes;

typedef struct {
  wander_status* ws;
} status_attributes;

typedef struct fauna_s {
  // base members
  node position;
  time born;
  char* explored; // known places on map

  // module members
  gene_attributes* genes;
  status_attributes* status;

  // data structure
  struct fauna_s* next;
} fauna;


// basic functions
fauna* fauna_new(world* w, node spawn_node);
void fauna_free(fauna* f);
void fauna_remove(fauna *head, fauna *f);
void fauna_remove_all(fauna* head);
fauna* fauna_add(fauna* head, world* w, node spawn_node);
fauna* fauna_at(fauna* head, node position);

#endif
