#include "world.h"

World::World()
{
    scenes.clear();
    Scene *scene = new Scene();
    scenes.push_back(scene);

    lights = scene->get_all_lights();
}
