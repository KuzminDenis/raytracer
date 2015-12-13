#include "sphere.h"

Sphere::Sphere() : center(glm::vec3(0, 0, 0)),
                   radius(0.0f),
                   material() { }

Sphere::Sphere(glm::vec3 center_p, float radius_p, Material material_p) :
    center(center_p),
    radius(radius_p),
    material(material_p) { }

bool Sphere::is_intersected(Ray &ray, float max_distance)
{
    glm::vec3 origin = ray.get_origin();
    glm::vec3 direction = ray.get_direction();
    float distance = 0.0f;

    bool sphere_intersected =
            glm::intersectRaySphere(origin, direction,
                                    center, radius * radius,
                                    distance);
    if (sphere_intersected && distance > 0.001f && distance < max_distance)
        return true;

    return false;
}

Intersection_info Sphere::intersection(Ray &ray)
{
    Intersection_info result;

    glm::vec3 normal = glm::vec3(0, 0, 0);
    glm::vec3 origin = ray.get_origin();
    glm::vec3 direction = ray.get_direction();
    glm::vec3 position = glm::vec3(0, 0, 0);

    bool sphere_intersected =
            glm::intersectRaySphere(origin, direction,
                                    center, radius,
                                    position, normal);
    if (sphere_intersected)
    {
        float distance = 0.0f;
        glm::intersectRaySphere(origin, direction,
                                center, radius * radius,
                                distance);
        if (distance < 0.001f)
            return result;

        result.is_intersected = true;
        result.normal = normal;
        result.intersection_point = position;
        result.material = material;
        result.distance = distance;
    }

    return result;
}
