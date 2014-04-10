#include "minunit.h"
#include "utility.c"
#include "wander.c"

char *test_wander()
{
  // TODO
  return NULL;
}

char *all_tests() {
  mu_suite_start();
  
  mu_run_test(test_wander);

  return NULL;
}

RUN_TESTS(all_tests);
