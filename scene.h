#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <ctime>

#include "lib/glm/glm/glm.hpp"

#include "types.h"

#include "triangle.h"
#include "light_source.h"
#include "scene_object.h"
#include "sphere.h"
#include "plane.h"

class Scene
{
    std::vector <Scene_object*> objects;
    std::vector <Light_source*> lights;

public:

    Scene();
    Scene(int a);

    void add_object(Scene_object *object)
    {
        objects.push_back(object);
    }

    void add_light(Light_source *light)
    {
        lights.push_back(light);
    }

    int get_objects_count() { return objects.size(); }
    Scene_object* get_object(int object_id)
    {
        return objects[object_id];
    }

    std::vector <Light_source*> get_all_lights() { return lights; }
    int get_lights_count() { return lights.size(); }
    Light_source* get_light(int light_id) { return lights[light_id]; }
};

class Scene_builder
{
public:
    Scene_builder() { }
    Scene* build_scene(glm::vec3 scene_center,
                       int objects_count, int mode);
    ~Scene_builder() { }
};


#endif // SCENE_H
