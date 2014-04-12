#ifndef WANDER_H_INCLUDED
#define WANDER_H_INCLUDED

#include "fauna.h"
#include "map.h"
#include "types.h"
#include "utility.h"
#include "world.h"

#define WANDER_MAX_PERTURBATION_ATTEMPTS 10 /* necessary for singly disconnected nodes  */
#define M_PI		3.14159265358979323846	/* pi */
#define RE_3_PI_I_8 0.3826834323650897717284599840303988667613445624856270414338 /* Re{e^{3pi/8}} */

typedef struct {
  double (*perturb_angle)(double);
  double (*derived_angle)(double, double);
} wander_parameters;

node wander(world* w,
	    wander_parameters* params,
	    fauna* f);
node node_from_angle(map* m,
		     node current,
		     double angle);
wander_status* wander_status_random();

// basic implementation
node wander_basic(world* w,
		  fauna* f);
double perturb_angle_basic(double angle);
double derived_angle_basic(double old_angle, double perturbed_angle);

#endif
