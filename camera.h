#ifndef CAMERA_H
#define CAMERA_H

#include "math.h"
#include <vector>

#include "lib/glm/glm/glm.hpp"

#include "types.h"

class Camera
{
    glm::vec3 position;
    glm::vec3 direction_forward;
    glm::vec3 direction_upward;
    glm::vec3 direction_rightward;

    float view_angle;
    int x_resolution, y_resolution;

    float distance; // distance from camera to image plane
    glm::vec3 plane_center; // image plane center

    glm::vec3 half_right; // half-right image plane vector
    glm::vec3 half_up; // half-up image plane vector

    std::vector<glm::vec3> picture;

    void initialize_camera(Render_settings settings_p);

public:

    Camera();
    Camera(Render_settings settings_p);

    glm::vec3 get_position() { return position; }
    glm::vec3 get_direction_forward() { return direction_forward; }
    glm::vec3 get_direction_upward() { return direction_upward; }
    glm::vec3 get_direction_rightward() { return direction_rightward; }

    int get_x_resolution() { return x_resolution; }
    int get_y_resolution() { return y_resolution; }
    float get_view_angle_rad() { return view_angle; }

    float get_distance() { return distance; }
    glm::vec3 get_plane_center() { return plane_center; }

    glm::vec3 get_half_right() { return half_right; }
    glm::vec3 get_half_up() { return half_up; }

    void set_pixel(int x, int y, glm::vec3 color)
    {
        picture[y * x_resolution + x] = color;
    }

    glm::vec3 get_pixel(int x, int y) { return picture[y * x_resolution + x]; }

    ~Camera() { }
};

#endif // CAMERA_H
