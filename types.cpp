#include "types.h"

Render_settings::Render_settings()
{
    file_name = "../render.png";
    img_width = 512;
    img_height = 512;
    max_level = 10;
    environment_color = glm::vec3(0, 0, 0);

    camera_position = glm::vec3(0, -8, 2);
    camera_direction_forward = glm::vec3(0, 1, 0);
    camera_direction_upward = glm::vec3(0, 0, 1);
    camera_view_angle = M_PI * 120.0f / 180;

    focal_length = 5.0;
    aperture_size = 2.0;
    rays_per_pixel = 16;
}

Render_settings::Render_settings(int heig,int widt,unsigned int level,float angle,std::string name,glm::vec3 color,glm::vec3 pos,glm::vec3 dire_f,glm::vec3 dire_up)
{
    //file_name = "../render.png";
    file_name=name;
    img_width = widt;
    img_height=heig;
    max_level = level;
    environment_color = color;

    camera_position = pos;
    camera_direction_forward = dire_f;
    camera_direction_upward = dire_up;
    camera_view_angle = M_PI * angle  / 180;
}

Material::Material()
{
    ambient_color = glm::vec3(0, 0, 255);
    diffuse_color = glm::vec3(0, 0, 255);
    shiness_color = glm::vec3(0, 0, 255);

    ambient_coeff = 0.2;
    diffuse_coeff = 0.6;
    shiness_coeff = 0.2;
    shiness_power = 10;
    specular_coeff = 0;
}

Intersection_info::Intersection_info() : material()
{
    is_intersected = false;
    distance = -1;
    intersected_mesh_id = -1;
    intersected_triangle_id = -1;
    intersection_point = glm::vec3(0, 0, 0);
    normal = glm::vec3(0, 0, 0);
}
