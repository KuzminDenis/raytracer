#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "lib/glm/glm/glm.hpp"
#include "lib/glm/glm/gtx/intersect.hpp"

#include "scene_object.h"
#include "ray.h"

class Triangle: public Scene_object
{
    glm::vec3 point1, point2, point3;
    Material material;

public:

    Triangle();
    Triangle(glm::vec3 point1_p, glm::vec3 point2_p, glm::vec3 point3_p,
             Material material);

    bool is_intersected(Ray &ray, float max_distance);
    Intersection_info intersection(Ray &ray);

    glm::vec3 get_point1() { return point1; }
    glm::vec3 get_point2() { return point2; }
    glm::vec3 get_point3() { return point3; }

    ~Triangle() { }
};

#endif // TRIANGLE_H
