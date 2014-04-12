#ifndef FAUNA_H_INCLUDED
#define FAUNA_H_INCLUDED

#include "types.h"
#include "wander.h"
#include "world.h"

#define FAUNA_NODE_UNEXPLORED 0x00
#define FAUNA_NODE_EXPLORED 0x01

// basic functions
fauna* fauna_new(world* w, node spawn_node);
void fauna_free(fauna* f);
void fauna_remove(fauna *head, fauna *f);
void fauna_remove_all(fauna* head);
fauna* fauna_add(fauna* head, world* w, node spawn_node);
fauna* fauna_at(fauna* head, node position);
void fauna_move(fauna* f, node n);
fauna* fauna_reproduce(world* w,
		       fauna* head,
		       fauna* f1,
		       fauna* f2);
#endif
