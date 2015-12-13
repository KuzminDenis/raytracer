#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "lib/glm/glm/glm.hpp"

#include "ray.h"

class Scene_object
{

public:

    // simply answers whether object is intersected by ray or not
    // works much faster than intersection()

    // max_distance is needed to make sure that intersection between
    // ray and light source is not happening on the oposite side
    // of light source
    virtual bool is_intersected(Ray &ray, float max_distance) = 0;

    // return full information about intersection between object and ray
    virtual Intersection_info intersection(Ray &ray) = 0;

    virtual ~Scene_object() { }
};

#endif // SCENE_OBJECT_H
