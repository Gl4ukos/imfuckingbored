#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record {
  public:
    point3 p;
    vec3 normal;
    double t;
};

class hittable {
  public:
    // Virtual means that this function can be overridden in derived classes, and C++ will decide at runtime which version to call.
    virtual ~hittable() = default; // "~" for destructor

    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0; // =0 means that the function is abstract
};

#endif