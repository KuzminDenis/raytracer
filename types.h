#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <math.h>

#include "lib/glm/glm/glm.hpp"

struct Render_settings
{
    std::string file_name;
    int img_width, img_height;
    unsigned int max_level;
    glm::vec3 environment_color;

    glm::vec3 camera_position;
    glm::vec3 camera_direction_forward;
    glm::vec3 camera_direction_upward;
    float camera_view_angle;

    float focal_length;
    float aperture_size;
    int rays_per_pixel;

    Render_settings();

    Render_settings(int heig,int widt,unsigned int level,float angle,std::string name, glm::vec3 color,glm::vec3 pos,glm::vec3 dire_f,glm::vec3 dire_up);
};

struct Material
{
    glm::vec3 ambient_color;
    glm::vec3 diffuse_color;
    glm::vec3 shiness_color;

    float ambient_coeff;
    float diffuse_coeff;
    float shiness_coeff;
    float shiness_power;
    float specular_coeff;

    Material();
};

struct Intersection_info
{
    bool is_intersected;
    float distance;
    int intersected_mesh_id;
    int intersected_triangle_id;
    glm::vec3 intersection_point;
    glm::vec3 normal;
    Material material;

    Intersection_info();
};

#endif // TYPES_H
