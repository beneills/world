#ifndef WANDER_H_INCLUDED
#define WANDER_H_INCLUDED

// necessary for singly disconnected nodes 
#define WANDER_MAX_PERTURBATION_ATTEMPTS 10

typedef struct {
  double angle; // radians
} wander_status;

typedef struct {
  double (*perturb_angle)(double);
  double (*derived_angle)(double, double);
} wander_parameters;


#endif
