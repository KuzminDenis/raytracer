#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <omp.h>
#include "ui_mydialog.h"

#include "lib/glm/glm/glm.hpp"
#include "lib/FreeImage/Source/FreeImage.h"

#include "types.h"

#include "world.h"
#include "camera.h"
#include "tracer.h"
#include "ray.h"

class Renderer
{
    Render_settings settings;

    static Renderer* _instance;

protected:

    Renderer(Render_settings settings_p);

public:

    static Renderer *Instance(Render_settings settings_p = Render_settings());

    Ray make_ray(Camera &camera, int x, int y); // from camera to (x,y) pixel
                                                // on image plane

    // store an image of the world into camera's .picture matrix
    void render_image(World *world, Camera &camera, Tracer &tracer,
                      Ui::MyDialog * ui);

    // save camera's .picture matrix into file
    void save_image(Camera &camera);

    void update_settings(Render_settings settings_p)
    {
        settings = settings_p;
    }
};

#endif // RENDERER_H
