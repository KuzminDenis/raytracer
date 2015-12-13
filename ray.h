#ifndef RAY_H
#define RAY_H

#include "lib/glm/glm/glm.hpp"

#include "types.h"

class Ray
{
    glm::vec3 origin;
    glm::vec3 direction;

    // depth of recursion during reflections
    unsigned int level;

public:

    Ray();
    Ray(glm::vec3 origin_p, glm::vec3 direction_p, int level_p);

    glm::vec3 get_origin() { return origin; }
    glm::vec3 get_direction() { return direction; }
    unsigned int get_level() { return level; }

    ~Ray() { }
};

#endif // RAY_H
