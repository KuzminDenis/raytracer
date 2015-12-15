#include "world.h"

World::World()
{
    builder = new Scene_builder();
    scenes.clear();

    Scene *scene = new Scene(1);
    scenes.push_back(scene);

    lights = scene->get_all_lights();
}

void World::add_scene(glm::vec3 scene_center, int object_count, int mode)
{
    Scene *scene = builder->build_scene(scene_center, object_count, mode);
    scenes.push_back(scene);
}

void WorldIterator::next()
{
    current_object++;
    Scene *scene = world->get_scene(current_scene);
    if (current_object < scene->get_objects_count())
        return;

    current_scene++;
    if (current_scene == world->get_scenes_count())
    {
        return;
    }

    while (current_scene < world->get_scenes_count())
    {
        Scene *scene = world->get_scene(current_scene);
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
    if (world->get_scenes_count() > 0)
        current_scene = 0;
    else
    {
        current_scene = -1;
        return;
    }

    while (current_scene < world->get_scenes_count())
    {
        Scene *scene = world->get_scene(current_scene);
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
    Scene *scene = world->get_scene(current_scene);
    return scene->get_object(current_object);
}

bool WorldIterator::done()
{
    if (current_scene == -1)
        return true;

    if (current_scene == world->get_scenes_count())
        return true;

    if (current_scene == (world->get_scenes_count()-1) && current_object == -1)
        return true;

    if (current_scene < world->get_scenes_count()-1)
        return false;

    Scene *scene = world->get_scene(current_scene);
    if (current_object >= scene->get_objects_count())
        return true;
    return false;
}
