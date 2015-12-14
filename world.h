#ifndef WORLD_H
#define WORLD_H

#include "types.h"

#include "scene.h"
#include "scene_object.h"
#include "light_source.h"

class World
{
    std::vector <Scene*> scenes;
    std::vector <Light_source*> lights;

public:

    World();

    int get_scenes_count() { return scenes.size(); }
    Scene *get_scene(int scene_id) { return scenes[scene_id]; }

    Light_source *get_light(int light_id) { return lights[light_id]; }
    int get_lights_count() { return lights.size(); }

    ~World() { }
};

class WorldIterator
{
    World world;

    int current_scene;
    int current_object;

public:

    WorldIterator(World &world_p)
    {
        world = world_p;
    }

    void next();
    void init();
    Scene_object* get_object();
    bool done();

    ~WorldIterator() { }
};

#endif // WORLD_H
