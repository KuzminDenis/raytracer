#include "plane.h"

Plane::Plane() : origin(glm::vec3(0, 0, 0)),
                 normal(glm::vec3(0, 0, 0)),
                 material() { }

Plane::Plane(glm::vec3 origin_p, glm::vec3 normal_p,
             Material material_p) :
    origin(origin_p),
    normal(normal_p),
    material(material_p) { }

bool Plane::is_intersected(Ray &ray, float max_distance)
{
    float distance;

    glm::vec3 ray_origin = ray.get_origin();
    glm::vec3 ray_direction = ray.get_direction();
    bool plane_intersected =
        glm::intersectRayPlane(ray_origin, ray_direction,
                               origin, normal,
                               distance);

    if (plane_intersected && distance > 0.001f && distance < max_distance)
        return true;

    return false;
}

Intersection_info Plane::intersection(Ray &ray)
{
    Intersection_info result; // initialized by default constructor

    float distance;
    glm::vec3 ray_origin = ray.get_origin();
    glm::vec3 ray_direction = ray.get_direction();
    bool plane_intersected =
        glm::intersectRayPlane(ray_origin, ray_direction,
                               origin, normal,
                               distance);

    if (plane_intersected && distance > 0.001f)
    {
        result.is_intersected = true;
        result.distance = distance;
        result.intersection_point = ray.get_origin() +
                                    ray.get_direction() * distance;

        result.normal = glm::normalize(normal);
        result.material = material;
    }

    return result;
}
