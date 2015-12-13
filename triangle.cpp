#include "triangle.h"

Triangle::Triangle() : point1(0, 0, 0),
                       point2(0, 0, 0),
                       point3(0, 0, 0),
                       material() { }

Triangle::Triangle(glm::vec3 point1_p, glm::vec3 point2_p, glm::vec3 point3_p,
                   Material material_p) :
    point1(point1_p),
    point2(point2_p),
    point3(point3_p),
    material(material_p) { }

bool Triangle::is_intersected(Ray &ray, float max_distance)
{
    glm::vec3 bary_position;
    glm::vec3 origin = ray.get_origin();
    glm::vec3 direction = ray.get_direction();

    bool triangle_intersected =
            glm::intersectRayTriangle(origin, direction,
                                      point1, point2, point3,
                                      bary_position);

    if (triangle_intersected && bary_position.z > 0.001f &&
        bary_position.z < max_distance)
    {
        return true;
    }

    return false;
}

Intersection_info Triangle::intersection(Ray &ray)
{
    Intersection_info result;

    glm::vec3 bary_position;
    glm::vec3 origin = ray.get_origin();
    glm::vec3 direction = ray.get_direction();

    bool triangle_intersected =
            glm::intersectRayTriangle(origin, direction,
                                      point1, point2, point3,
                                      bary_position);

    if (triangle_intersected && bary_position.z > 0.001f)
    {
        result.is_intersected = true;
        result.distance = bary_position.z;
        result.intersection_point = ray.get_origin() +
                                    ray.get_direction() * bary_position.z;
        glm::vec3 a1 = point2 - point1;
        glm::vec3 a2 = point3 - point1;
        result.normal = glm::cross(a1, a2);
        result.normal = glm::normalize(result.normal);
        result.material = material;
    }

    return result;
}

/*bool Triangle::is_intersected(Ray &ray, float max_distance)
{
    glm::vec3 ray_origin = ray.get_origin();
    glm::vec3 ray_direction = ray.get_direction();
    float distance = 0;

    glm::vec3 edge1 = point2 - point1;
    glm::vec3 edge2 = point3 - point1;

    glm::vec3 pvec = glm::cross(ray_direction, edge2);
    float det = glm::dot(edge1, pvec);

    float epsilon = 0.00001;

    if (det > -epsilon && det < epsilon)
        return false;

    float inv_det = 1.0 / det;

    glm::vec3 tvec = ray_origin - point1;

    float u = glm::dot(tvec, pvec) * inv_det;
    if (u < 0.0 || u > 1.0)
        return false;

    glm::vec3 qvec = glm::cross(tvec, edge1);

    float v = glm::dot(ray_direction, qvec) * inv_det;
    if (v < 0.0 || u + v > 1.0)
        return false;

    distance = glm::dot(edge2, qvec) * inv_det;

    if (max_distance > 0 && distance > max_distance)
        return false;

    return true;
}

*/









