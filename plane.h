#ifndef PLANE_H
#define PLANE_H

#include "lib/glm/glm/glm.hpp"
#include "lib/glm/glm/gtx/intersect.hpp"

#include "types.h"

#include "scene_object.h"
#include "ray.h"

// infinite plane defined by point and normal
class Plane : public Scene_object
{
    glm::vec3 origin, normal;
    Material material;

public:

    Plane();
    Plane(glm::vec3 origin_p, glm::vec3 normal_p,
          Material material_p);

    bool is_intersected(Ray &ray, float max_distance);
    Intersection_info intersection(Ray &ray);

    glm::vec3 get_origin() { return origin; }
    glm::vec3 get_normal() { return normal; }
    Material get_material() { return material; }

    ~Plane() { }
};

#endif // PLANE_H
