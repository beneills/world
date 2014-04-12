#include "generate_fauna.h"

static map* m_g = NULL;		/* TODO this is necessary currently */

// tries to place n fauna on random empty tiles
// but may place some or all (may return NULL)
fauna* fauna_generate(world* w, unsigned int n) {
  fauna* f = NULL;

  // set map global variable, for access withing fauna_open_node
  m_g = w->m;

  // we don't care about any of the parameter functionality,
  //   except that the fauna is not on an impassable node
  generation_parameters* fauna_params = null_params;
  fauna_params->open_node = &fauna_open_node;

  seeds* head = seeds_generate(w->m->width, w->m->height, n, fauna_params);

  for ( seed* s = head;
	s != NULL;
	s = s->next ) {
    fauna_add(f, w, NODE(s->x, s->y));
  }
  seeds_free(head);

  return f;
}

bool fauna_open_node(int x, int y) {
  if ( MAP_ELEMENT(m_g x, y) == MAP_EL_IMPASSABLE ) {
    return false;
  }
  return true;
}
