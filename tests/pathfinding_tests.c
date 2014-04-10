#include "minunit.h"
#include "pathfinding.h"

char *test_node_list_add()
{
  /* node_list* head = node_list_add(0, 0, 0, 5, NULL, NULL); */
  /* node_list* head = node_list_add(0, 0, 0, 5, NULL, NULL); */
  return NULL;
}

char *all_tests() {
  mu_suite_start();
  
  mu_run_test(test_node_list_add);
  
  return NULL;
}

RUN_TESTS(all_tests);
