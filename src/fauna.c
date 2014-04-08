#include <stdlib.h>

#include "fauna.h"
#include "utility.h"

fauna* fauna_new(unsigned int map_width, unsigned int map_height, unsigned int x, unsigned int y) {
  fauna* f = (fauna *) SAFEMALLOC(sizeof(fauna));
  f->x = x;
  f->y = y;
  f->next = NULL;
  f->explored = (char *) SAFEMALLOC(sizeof(char) * map_width * map_height);
  return f;
}

void fauna_free(fauna* f) {
  free(f->explored);
  free(f);
}

// returns pointer to added fauna
// starts new list if passed NULL
fauna* fauna_add(unsigned int map_width, unsigned int map_height, fauna* head, unsigned int x, unsigned int y) {
  fauna* f = fauna_new(map_width, map_height, x, y);
  if ( head != NULL ) {
    for ( ; head->next != NULL; head = head->next ){}
    head->next = f;
  }
  return f;
}

void fauna_remove(fauna *head, fauna *f) {
  for ( ; &head->next != &f; head = head->next ) {}
  head->next = f->next;
  fauna_free(f);
}

// returns NULL if not found
fauna* fauna_at(fauna* head, unsigned int x, unsigned int y) {
  for ( ;
	head != NULL && ( head->x != x || head->y != y );
	head = head->next ) {}
  return head;
}

// tries to place n fauna on random empty tiles
// but may place some or all (may return NULL)
fauna* fauna_generate(map* m, unsigned int n) {
  fauna* head = NULL;
  fauna* tmp;
  for ( int i = 0,
	  successes = 0,
	  x = 0,
	  y = 0;
	i < FAUNA_GENERATE_MAX &&
	  successes < n;
	++i ) {
    x = integer_uniform_random(m->width);
    y = integer_uniform_random(m->height);

    if ( map_element(m, x, y) == MAP_EL_EMPTY ) {
      tmp = fauna_add(m->width, m->height, head, x, y);
      if ( head == NULL ) { head = tmp; } // set head only once
      ++successes;
    }
  }
  return head;
}
