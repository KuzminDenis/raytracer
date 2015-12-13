#ifndef WORLD_H
#define WORLD_H

#include "types.h"

#include "scene.h"
#include "light_source.h"

class World
{
    std::vector <Scene*> scenes;
    std::vector <Light_source*> lights;

public:

    World();

    unsigned int get_scenes_count() { return scenes.size(); }
    Scene *get_scene(unsigned int scene_id) { return scenes[scene_id]; }

    Light_source *get_light(unsigned int light_id) { return lights[light_id]; }
    unsigned int get_lights_count() { return lights.size(); }

    ~World() { }
};

#endif // WORLD_H
