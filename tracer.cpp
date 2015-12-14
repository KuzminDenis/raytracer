#include "tracer.h"

Tracer::Tracer() : settings() { }
Tracer::Tracer(Render_settings settings_p) : settings(settings_p) { }

bool Tracer::trace_shadow_ray(Ray &ray, World &world, float light_distance)
{
    WorldIterator iterator(world);
    iterator.init();
    while (!iterator.done())
    {
        Scene_object *object = iterator.get_object();
        bool object_intersection =
                object->is_intersected(ray, light_distance);
        if (object_intersection)
        {
            return true;
        }

        iterator.next();
    }

    return false;
}

glm::vec3 Tracer::trace_reflection(Intersection_info info,
                                   Ray &ray, World &world, Camera &camera)
{
    float scalar = glm::dot(ray.get_direction(), info.normal);
    scalar *= -2;

    glm::vec3 reflection_direction =
            ray.get_direction() + info.normal * (float) (scalar);

    glm::vec3 epsilon = info.normal * 0.001f;
    Ray reflected_ray = Ray(info.intersection_point + epsilon,
                            reflection_direction, ray.get_level() + 1);
    glm::vec3 reflection_color = trace_ray(reflected_ray, world, camera);
    return reflection_color;
}

glm::vec3 Tracer::contribution_by_light(Intersection_info &intersection,
                                        World &world, Camera &camera,
                                        Light_source *light)
{
//    glm::vec3 ambient_color = intersection.material.ambient_color;
    glm::vec3 diffuse_color = intersection.material.diffuse_color;
    glm::vec3 shiness_color = intersection.material.shiness_color;

//    float ambient_coeff = intersection.material.ambient_coeff;
    float diffuse_coeff = intersection.material.diffuse_coeff;
    float shiness_coeff = intersection.material.shiness_coeff;
    float shiness_power = intersection.material.shiness_power;

    glm::vec3 color = glm::vec3(0, 0, 0);

    glm::vec3 light_position = light->get_position();
    glm::vec3 shadow_direction = light_position -
                                 intersection.intersection_point;
    float light_distance = glm::length(shadow_direction);
    shadow_direction = glm::normalize(shadow_direction);

    glm::vec3 epsilon = intersection.normal * 0.001f;
    Ray shadow_ray = Ray(intersection.intersection_point + epsilon,
                         shadow_direction, 1);

    bool in_shadow = trace_shadow_ray(shadow_ray, world, light_distance);

    // if point in shadow
    if (in_shadow)
        return glm::vec3(0, 0, 0);

    // else : point is lit

    glm::vec3 camera_position = camera.get_position();
    glm::vec3 v = camera_position - intersection.intersection_point;
    v = glm::normalize(v);

    glm::vec3 r = glm::reflect(v, intersection.normal);
    r = -r;
    r = glm::normalize(r);

    glm::vec3 diff = diffuse_color *
        (float) std::max(glm::dot(intersection.normal, shadow_direction),
                         0.0f);

    glm::vec3 shine = shiness_color *
        (float) pow(std::max(glm::dot(shadow_direction, r), 0.0f),
                    shiness_power);

    // process attenuation

    float k_const_attenuation = light->get_k_const_attenuation();
    float k_linear_attenuation = light->get_k_linear_attenuation();
    float k_quadric_attenuation = light->get_k_quadric_attenuation();

    float attenuation =
        1.0 / ( k_const_attenuation +
                k_linear_attenuation * light_distance +
                k_quadric_attenuation * light_distance * light_distance );

//    diff *= attenuation;
//    shine *= attenuation;

    color = //(ambient_coeff * ambient_color) +
            (diffuse_coeff * diff) +
            (shiness_coeff * shine);

    return color;
}

glm::vec3 Tracer::apply_lightning(Intersection_info &intersection,
                                  World &world, Camera &camera)
{
    unsigned int lights_count = world.get_lights_count();
    float coeff;
    if (lights_count > 0)
        coeff = 1.0f / lights_count;
    else
        coeff = 1.0f;

    //coeff = 1.0;
    glm::vec3 result_color = intersection.material.ambient_coeff *
                             intersection.material.ambient_color;

    // iterate through all the lights in the world
    for (unsigned int light_id = 0; light_id < lights_count; light_id++)
    {
        Light_source* light = world.get_light(light_id);
        glm::vec3 color = contribution_by_light(intersection, world, camera,
                                                light);
        result_color += coeff * color;
    }

    return result_color;
}

void Tracer::fix_color(glm::vec3 &color)
{
    if (color.x > 255)
        color.x = 255;
    if (color.y > 255)
        color.y = 255;
    if (color.z > 255)
        color.z = 255;
}

Intersection_info Tracer::find_closest_intersection(Ray &ray, World &world)
{
    Intersection_info closest_intersection; // initialized by constructor

    float minimal_distance = 99999.0;

    WorldIterator iterator(world);
    iterator.init();
    while (!iterator.done())
    {
        Scene_object *object = iterator.get_object();

        Intersection_info object_intersection = object->intersection(ray);

        if (object_intersection.is_intersected &&
            object_intersection.distance > 0.0f &&
            object_intersection.distance < minimal_distance)
        {
            minimal_distance = object_intersection.distance;
            closest_intersection = object_intersection;
        }

        iterator.next();
    }

    return closest_intersection;
}

glm::vec3 Tracer::trace_ray(Ray &ray, World &world, Camera &camera)
{
    if (ray.get_level() > settings.max_level)
        return settings.environment_color;

    Intersection_info closest_intersection =
            find_closest_intersection(ray, world);

    // ray does not hit any object in the world
    if (!closest_intersection.is_intersected)
        return settings.environment_color;

    // else : ray intersects some object

    // process lightning
    glm::vec3 color =
        apply_lightning(closest_intersection, world, camera);

    // process reflections
    if (closest_intersection.material.specular_coeff > 0.01)
    {
        color += closest_intersection.material.specular_coeff *
                 trace_reflection(closest_intersection, ray, world, camera);
    }

    // ensure that components of color are not greater than 255
    fix_color(color);

    return color;
}
