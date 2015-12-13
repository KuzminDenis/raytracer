#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "lib/glm/glm/glm.hpp"

#include "types.h"

#include "triangle.h"
#include "light_source.h"
#include "scene_object.h"
#include "sphere.h"
#include "plane.h"
#include "model.h"

class Scene
{
    std::vector <Scene_object*> objects;
    std::vector <Light_source*> lights;

public:

    Scene();

    unsigned int get_objects_count() { return objects.size(); }
    Scene_object* get_object(unsigned int object_id)
    {
        return objects[object_id];
    }

    std::vector <Light_source*> get_all_lights() { return lights; }
    unsigned int get_lights_count() { return lights.size(); }
    Light_source* get_light(unsigned int light_id) { return lights[light_id]; }
};

#endif // SCENE_H
