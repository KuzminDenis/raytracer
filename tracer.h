#ifndef TRACER_H
#define TRACER_H

#include <iostream>

#include "lib/glm/glm/glm.hpp"

#include "types.h"

#include "ray.h"
#include "world.h"
#include "camera.h"
#include "scene_object.h"
#include "math.h"

class Tracer
{
    Render_settings settings;

    void fix_color(glm::vec3 &color);
    Intersection_info find_closest_intersection(Ray &ray, World &world);
    glm::vec3 contribution_by_light(Intersection_info &intersection,
                                    World &world, Camera &camera,
                                    Light_source *light);
public:

    Tracer();
    Tracer(Render_settings settings_p);

    glm::vec3 apply_lightning(Intersection_info &intersection,
                              World &world, Camera &camera);

    glm::vec3 trace_ray(Ray &ray, World &world, Camera &camera);
    bool trace_shadow_ray(Ray &ray, World &world, float light_distance);
    glm::vec3 trace_reflection(Intersection_info info,
                               Ray &ray, World &world, Camera &camera);

    ~Tracer() { }
};

#endif // TRACER_H
