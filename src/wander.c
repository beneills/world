#include "math.h"

#include "fauna.h"
#include "map.h"
#include "utility.h"
#include "wander.h"

#define M_PI		3.14159265358979323846	/* pi */
#define RE_3_PI_I_8 0.3826834323650897717284599840303988667613445624856270414338


double perturb_angle_basic(double angle) {
  // TODO
  double perturbation = uniform_random() * 2 * M_PI - M_PI;
  return angle + perturbation;
}

double derived_angle_basic(double old_angle, double perturbed_angle) {
  // TODO
  return (old_angle + perturbed_angle) / 2.0;
}

node node_from_angle(node current, double angle) {
  double c = cos(angle);
  double s = sin(angle);

  current.x += ( c < -RE_3_PI_I_8 ) ? -1 :
    ( c < RE_3_PI_I_8 ) ? 0 :
    1;
  current.y += ( s < -RE_3_PI_I_8 ) ? -1 :
    ( s < RE_3_PI_I_8 ) ? 0 :
    1;

  return current;
}

// moves fauna to next node and returns that node
// TODO use f->wander_status
node wander(map* m,
	    wander_parameters* params,
	    wander_status* s,
	    fauna* f) {
  double perturbed_angle;
  node n, current = {
    .x = f->x,
    .y = f->y
  };
  debug("1\n");
  for ( unsigned int i = 0; i < WANDER_MAX_PERTURBATION_ATTEMPTS; ++i ) {
    perturbed_angle = (*params->perturb_angle)(s->angle);
    n = node_from_angle(current, perturbed_angle);
    if ( map_valid(m, n.x, n.y) &&
	 map_element(m, n.x, n.y) == MAP_EL_EMPTY ) {
      // update angle
      s->angle = (*params->derived_angle)(s->angle, perturbed_angle);
      // update fauna position
      f->x = n.x;
      f->y = n.y;
      // TODO explored
      return n;
    }
  }
  // default to staying still
  return current;
}

// convienience method to use basic parameters
node wander_basic(map* m,
		  wander_status* s,
		  fauna* f) {
  wander_parameters p = {
    .perturb_angle = &perturb_angle_basic,
    .derived_angle = &derived_angle_basic
  };
  return wander(m, &p, s, f);
}

wander_status* wander_status_random() {
  wander_status* w = (wander_status *) SAFEMALLOC(sizeof(wander_status));
  w->angle = uniform_random() * 2 * M_PI;
  return w;
}
