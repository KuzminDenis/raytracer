#include "mainwindow.h"
#include <QApplication>

#include <stdio.h>
#include <stdlib.h>

#include "lib/glm/glm/glm.hpp"

#include "types.h"

#include "renderer.h"
#include "world.h"
#include "camera.h"
#include "tracer.h"

#include <omp.h>

int main(int argc, char *argv[])
{
    World world;

    Render_settings settings;

    Renderer renderer(settings);
    Tracer tracer(settings);
    Camera camera(settings);

    renderer.render_image(world, camera, tracer);
    renderer.save_image(camera);

    QApplication a(argc, argv);
    MainWindow w;
    w.resize(settings.img_width, settings.img_height);
    w.show();

    return a.exec();
}
