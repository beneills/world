#include <assert.h>
#include <stdlib.h>

#include "fauna.h"
#include "utility.h"


// return new fauna object, sensibly initialized
fauna* fauna_new(world* w, node spawn_node) {
  fauna* f = (fauna *) SAFEMALLOC(sizeof(fauna));

  // base members
  f->position = spawn_node;
  f->born = 0;
  f->explored = (char *)
    SAFEMALLOC(sizeof(char) * w->m->width * w->m->height);
  // TODO explored set spawn_node

  // module members
  f->genes = (gene_attributes *)
    SAFEMALLOC(sizeof(gene_attributes));
  f->status = (status_attributes *)
    SAFEMALLOC(sizeof(status_attributes));
  // TODO init these?

  // data structure
  f->next = NULL;

  return f;
}

// free ONE fauna object's memory
void fauna_free(fauna* f) {
  free(f->explored);
  free(f->genes);
  free(f->status);
  free(f);
}

// remove ONE fauna object
// TODO test
void fauna_remove(fauna *head, fauna *f) {
  for ( ; head->next != f; head = head->next ) {}
  head->next = f->next;		/* patch up the chain */
  fauna_free(f);
}

// remove entire fauna list
// TODO test
void fauna_remove_all(fauna* head) {
  for ( fauna* tmp = head->next;
	head != NULL;
	head = tmp, tmp = head->next ) {
    fauna_free(head);
  }
}

// add a fauna to end of list and return it
// if head == NULL, we start a new list seamlessly
// TODO test
fauna* fauna_add(fauna* head, world* w, node spawn_node) {
  fauna* f = fauna_new(w, spawn_node);
  if ( head != NULL ) {
    for ( ; head->next != NULL; head = head->next )
      ;				/* intentionally blank */
    head->next = f;
  }
  return f;
}

// return the first fauna found in list with given position,
//   starting at search_start
// returns NULL if no such fauna exists in list
// TODO test
fauna* fauna_at(fauna* search_start, node position) {
  for ( ;
	search_start != NULL &&
	  !NODE_EQ(search_start->position, position);
	search_start = search_start->next ) {}
  return search_start;
}

// move the fauna to a node
// NOTE there is no error checking: node must be valid
// TODO test
void fauna_move(fauna* f, node n) {
  f->position = n;
  // TODO explored
}


// add a new child fauna to the list and return it
fauna* fauna_reproduce(world* w,
		       fauna* head,
		       fauna* f1,
		       fauna* f2) {
  assert(f1->x == f2->x);
  assert(f1->y == f2->y);

  fauna* child = fauna_add(head, w, f1->x, f1->y);

  // TODO perturb

  return child;
}
