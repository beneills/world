#include "minunit.h"
#include "utility.c"
#include "heap.c"

char *test_heap_new_free()
{
  heap* h = heap_new(sizeof(int));
  heap_free(h);
  return NULL;
}

char *test_heap_push()
{
  heap* h = heap_new(sizeof(int));

  heap_push(h, 1);
  heap_push(h, 4);
  heap_push(h, 2);
  heap_push(h, 3);
  heap_push(h, 0);
  // TODO actually check
  heap_print(h);

  heap_free(h);
  return NULL;
}

char *all_tests() {
  mu_suite_start();
  
  mu_run_test(test_heap_new_free);
  mu_run_test(test_heap_push);
  return NULL;
}

RUN_TESTS(all_tests);
