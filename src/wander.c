#include <math.h>

#include "fauna.h"
#include "map.h"
#include "utility.h"
#include "wander.h"

// moves fauna to next node and returns that node
node wander(world* w,
	    wander_parameters* params,
	    fauna* f) {
  node n;
  double perturbed_angle;
  for ( unsigned int i = 0;
	i < WANDER_MAX_PERTURBATION_ATTEMPTS;
	++i ) {
    // calculate a perturbed angle and corresponding (valid) node
    perturbed_angle = (*params->perturb_angle)(f->status->wander);
    n = node_from_angle(f->position, perturbed_angle);

    // if this node is viable, move the fauna
    if ( MAP_ELEMENT(m, n.x, n.y) == MAP_EL_EMPTY ) {
      f->status->wander->angle = (*params->derived_angle)(s->angle,
							  perturbed_angle);
      fauna_move(f, n);
      break;
    }
  }

  return f->position;
}

// returns the (valid) node in direction of angle
//   will return current rather than going off edge
node node_from_angle(map* m,
		     node current,
		     double angle) {
  double c = cos(angle);
  double s = sin(angle);

  int dx = ( c < -RE_3_PI_I_8 ) ? -1 :
    ( c < RE_3_PI_I_8 ) ? 0 :
    1;
  int dy = ( s < -RE_3_PI_I_8 ) ? -1 :
    ( s < RE_3_PI_I_8 ) ? 0 :
    1;

  if ( MAP_NODE_VALID(m, current.x + dx, current.y + dy) ) {
    return {.x = (unsigned int) (current.x + dx),
	.y = (unsigned int) (current.y + dy)
	};
  }

  return current;		/* default */
}

// returns a random wander_status, currently just choosing
//   the angle uniformly
wander_status* wander_status_random() {
  wander_status* w = (wander_status *) SAFEMALLOC(sizeof(wander_status));
  w->angle = UNIFORM_RANDOM() * 2 * M_PI;
  return w;
}

// convienience method to use basic implementation
node wander_basic(world* w,
		  fauna* f) {
  wander_parameters* p = (wander_parameters *)
    SAFEMALLOC(sizeof(wander_parameters));
  p->perturb_angle = &perturb_angle_basic;
  p->derived_angle = &derived_angle_basic;
  
  return wander(w, p, f);
}

// uniform perturbation
// TODO use sensible distribution
double perturb_angle_basic(double angle) {
  double perturbation = uniform_random() * 2 * M_PI - M_PI;
  return angle + perturbation;
}

// linear interpolation
double derived_angle_basic(double old_angle, double perturbed_angle) {
  return (old_angle + perturbed_angle) / 2.0;
}
