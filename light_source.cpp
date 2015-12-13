#include "light_source.h"

Light_source::Light_source() :
    position(glm::vec3(0, -5, 0)),
    color(glm::vec3(255, 255, 255)),
    intensity(1.0f),
    state(true),
    k_const_attenuation(0.5f),
    k_linear_attenuation(0.0f),
    k_quadric_attenuation(0.05f) { }

Light_source::Light_source(glm::vec3 position_p) :
    position(position_p),
    color(glm::vec3(255, 255, 255)),
    intensity(1.0f),
    state(true),
    k_const_attenuation(0.5f),
    k_linear_attenuation(0.0f),
    k_quadric_attenuation(0.05f) { }
