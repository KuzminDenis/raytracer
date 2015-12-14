#include "world.h"

World::World()
{
    scenes.clear();

    Scene *scene = new Scene();
    scenes.push_back(scene);

    lights = scene->get_all_lights();
}

void WorldIterator::next()
{
    current_object++;
    Scene *scene = world.get_scene(current_scene);
    if (current_object < scene->get_objects_count())
        return;

    current_scene++;
    if (current_scene == world.get_scenes_count())
    {
        return;
    }

    while (current_scene < world.get_scenes_count())
    {
        Scene *scene = world.get_scene(current_scene);
        if (scene->get_objects_count() > 0)
        {
            current_object = 0;
            return;
        }

        current_scene++;
    }
}

void WorldIterator::init()
{
    if (world.get_scenes_count() > 0)
        current_scene = 0;
    else
    {
        current_scene = -1;
        return;
    }

    while (current_scene < world.get_scenes_count())
    {
        Scene *scene = world.get_scene(current_scene);
        if (scene->get_objects_count() > 0)
        {
            current_object = 0;
            return;
        }

        current_scene++;
    }
}

Scene_object* WorldIterator::get_object()
{
    Scene *scene = world.get_scene(current_scene);
    return scene->get_object(current_object);
}

bool WorldIterator::done()
{
    if (current_scene == -1)
        return true;

    if (current_scene == world.get_scenes_count())
        return true;

    if (current_scene == (world.get_scenes_count()-1) && current_object == -1)
        return true;

    if (current_scene < world.get_scenes_count()-1)
        return false;

    Scene *scene = world.get_scene(current_scene);
    if (current_object >= scene->get_objects_count())
        return true;
    return false;
}
