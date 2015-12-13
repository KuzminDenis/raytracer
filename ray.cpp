#include "ray.h"

Ray::Ray() : origin(glm::vec3(0, 0, 0)),
             direction(glm::vec3(0, 0, 0)),
             level(1) { }

Ray::Ray(glm::vec3 origin_p, glm::vec3 direction_p, int level_p) :
    origin(origin_p),
    direction(direction_p),
    level(level_p) { }
