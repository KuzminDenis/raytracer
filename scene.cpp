#include "scene.h"

Scene::Scene()
{
    objects.clear();
    lights.clear();
}

Scene::Scene(int a)
{
    Material material1;

    material1.ambient_color = glm::vec3(255, 0, 0);
    material1.diffuse_color = glm::vec3(255, 0, 0);
    material1.shiness_color = glm::vec3(255, 0, 0);

    material1.ambient_coeff = 0.1;
    material1.diffuse_coeff = 0.6;
    material1.shiness_coeff = 0.2;
    material1.shiness_power = 20;
    material1.specular_coeff = 0;

    Material material2;

    material2.ambient_color = glm::vec3(0, 255, 0);
    material2.diffuse_color = glm::vec3(0, 255, 0);
    material2.shiness_color = glm::vec3(0, 255, 0);

    material2.ambient_coeff = 0.1;
    material2.diffuse_coeff = 0.4;
    material2.shiness_coeff = 0.5;
    material2.shiness_power = 5;
    material2.specular_coeff = 0;

    Material material3;

    material3.ambient_color = glm::vec3(192, 192, 192);
    material3.diffuse_color = glm::vec3(192, 192, 192);
    material3.shiness_color = glm::vec3(192, 192, 192);

    material3.ambient_coeff = 0.05;
    material3.diffuse_coeff = 0.05;
    material3.shiness_coeff = 0.1;
    material3.shiness_power = 40;
    material3.specular_coeff = 0.8;

    Material material4;

    material4.ambient_color = glm::vec3(255, 255, 255);
    material4.diffuse_color = glm::vec3(255, 255, 255);
    material4.shiness_color = glm::vec3(255, 255, 255);

    material4.ambient_coeff = 0;
    material4.diffuse_coeff = 0;
    material4.shiness_coeff = 0;
    material4.shiness_power = 0;
    material4.specular_coeff = 1;

    Material material5;

    material5.ambient_color = glm::vec3(0, 0, 255);
    material5.diffuse_color = glm::vec3(0, 0, 255);
    material5.shiness_color = glm::vec3(0, 0, 255);

    material5.ambient_coeff = 0.1;
    material5.diffuse_coeff = 0.4;
    material5.shiness_coeff = 0.5;
    material5.shiness_power = 40;
    material5.specular_coeff = 0;

    Material material6;

    material6.ambient_color = glm::vec3(255, 0, 255);
    material6.diffuse_color = glm::vec3(255, 0, 255);
    material6.shiness_color = glm::vec3(255, 0, 255);

    material6.ambient_coeff = 0.1;
    material6.diffuse_coeff = 0.4;
    material6.shiness_coeff = 0.2;
    material6.shiness_power = 40;
    material6.specular_coeff = 0.3;

    objects.clear();

    // WALLS

    Plane *pln = new Plane(glm::vec3(0, 0, -5), glm::vec3(0, 0, 1), material1);
    objects.push_back(pln);

    pln = new Plane(glm::vec3(0, 5, 0), glm::vec3(0,-1, 0), material1);
    objects.push_back(pln);

    pln = new Plane(glm::vec3(0, -9, 0), glm::vec3(0, 1, 0), material1);
    objects.push_back(pln);

    pln = new Plane(glm::vec3(-7, 0, 0), glm::vec3(1, 0, 0), material1);
    objects.push_back(pln);

    pln = new Plane(glm::vec3(7, 0, 0), glm::vec3(-1, 0, 0), material1);
    objects.push_back(pln);

    pln = new Plane(glm::vec3(0, 0, 10), glm::vec3(0, 0, -1), material1);
    objects.push_back(pln);

    // OBJECTS

//    Sphere *sph = new Sphere(glm::vec3(-2, -1, -0.5), 1.25f, material2);
//    objects.push_back(sph);

//    sph = new Sphere(glm::vec3(2, -1, -0.5), 1.25f, material3);
//    objects.push_back(sph);

//    sph = new Sphere(glm::vec3(0, -1, 1.75), 1.25f, material3);
//    objects.push_back(sph);

//    sph = new Sphere(glm::vec3(-2, -1, 4), 1.25f, material5);
//    objects.push_back(sph);

//    sph = new Sphere(glm::vec3(2, -1, 4), 1.25f, material6);
//    objects.push_back(sph);

    // LIGHTS

    lights.clear();

    Light_source *lght = new Light_source(glm::vec3(-4, -8, 4.5));
    lights.push_back(lght);

    lght = new Light_source(glm::vec3(6, -6, 6));
    lights.push_back(lght);

    lght = new Light_source(glm::vec3(-6, -6, 6));
    lights.push_back(lght);
}

float random_float(float a, float b)
{
    return ( (b-a) * ( (float)rand() / RAND_MAX) ) + a;
}

Scene*
Scene_builder::build_scene(glm::vec3 scene_center,
                           int objects_count, int mode)
{
    Material material;
    Scene* scene = new Scene();

    if (mode == 0)
    {
        material.ambient_coeff = 0.3;
        material.diffuse_coeff = 0.5;
        material.shiness_coeff = 0.2;
        material.shiness_power = 20;
        material.specular_coeff = 0;
    }
    else
    {
        material.ambient_coeff = 0.1;
        material.diffuse_coeff = 0;
        material.shiness_coeff = 0.2;
        material.shiness_power = 20;
        material.specular_coeff = 0.7;
    }

    for (int object_id = 0; object_id < objects_count; object_id++)
    {
        float r = random_float(0, 255);
        float g = random_float(0, 255);
        float b = random_float(0, 255);

        material.ambient_color = glm::vec3((int)r, (int)g, (int)b);
        material.diffuse_color = glm::vec3((int)r, (int)g, (int)b);
        material.shiness_color = glm::vec3((int)r, (int)g, (int)b);

        float dx = random_float(1, 3);
        float dy = random_float(1, 3);
        float dz = random_float(1, 3);
        Scene_object *object =
                new Sphere(scene_center + glm::vec3(dx,dy,dz),
                           0.75f, material);
        scene->add_object(object);
    }

    return scene;
}





