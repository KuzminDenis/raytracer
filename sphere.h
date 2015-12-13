#ifndef SPHERE_H
#define SPHERE_H

#include "lib/glm/glm/glm.hpp"
#include "lib/glm/glm/gtx/intersect.hpp"

#include "scene_object.h"
#include "ray.h"

class Sphere : public Scene_object
{
    glm::vec3 center;
    float radius;
    Material material;

public:

    Sphere();
    Sphere(glm::vec3 center_p, float radius_p, Material material_p);

    bool is_intersected(Ray &ray, float max_distance);
    Intersection_info intersection(Ray &ray);

    glm::vec3 get_center() { return center; }
    float get_radius() { return radius; }
    Material get_material() { return material; }

    void set_center(glm::vec3 center_p) { center = center_p; }
    void set_radius(float radius_p) {radius = radius_p; }

    ~Sphere() { }
};

#endif // SPHERE_H
