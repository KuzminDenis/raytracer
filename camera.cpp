#include "camera.h"

void Camera::initialize_camera(Render_settings settings_p)
{
    position = settings_p.camera_position;

    direction_forward = glm::normalize(settings_p.camera_direction_forward);
    direction_upward = glm::normalize(settings_p.camera_direction_upward);

    // rightward direction is calculated according to
    // directions upward and forward
    direction_rightward =
            glm::normalize(glm::cross(direction_forward, direction_upward));

    view_angle = settings_p.camera_view_angle;

    x_resolution = settings_p.img_width;
    y_resolution = settings_p.img_height;
    picture.resize(x_resolution * y_resolution);

    // distance to image plot is calculated according to
    // resolution and view angle
    distance = (1.0f * x_resolution / 2) / tan(view_angle / 2);

    plane_center = position + distance * direction_forward;
    half_right = direction_rightward * (float) (tan(view_angle / 2) * distance);
    half_up = direction_upward *
              (float) (tan(view_angle / 2) *
                      (y_resolution * 1.0f / x_resolution) * distance);
}

Camera::Camera()
{
    // use default settings
    Render_settings settings;
    initialize_camera(settings);
}

Camera::Camera(Render_settings settings_p)
{
    initialize_camera(settings_p);
}
