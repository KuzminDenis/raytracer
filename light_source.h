#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include "lib/glm/glm/glm.hpp"

#include "types.h"

class Light_source
{
    glm::vec3 position;

    glm::vec3 color; // RGB (0..255, 0..255, 0..255)
    float intensity; // 0.0f to 1.0f
    bool state; // ON or OFF

    // attenuation coefficients
    float k_const_attenuation;
    float k_linear_attenuation;
    float k_quadric_attenuation;

public:

    Light_source();
    Light_source(glm::vec3 position_p);

    glm::vec3 get_position() { return position; }
    glm::vec3 get_color() { return color; }

    float get_intensity() { return intensity; }
    bool get_state() { return state; }

    void turn_on() { state = true; }
    void turn_off() { state = false; }

    float get_k_const_attenuation() { return k_const_attenuation; }
    float get_k_linear_attenuation() { return k_linear_attenuation; }
    float get_k_quadric_attenuation() { return k_quadric_attenuation; }

};

#endif // LIGHT_SOURCE_H
