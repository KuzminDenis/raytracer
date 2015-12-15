#include "mainwindow.h"
#include <QApplication>
#include <qpushbutton.h>
#include <qapplication.h>
#include "qlabel.h"
#include "dialog.h"
#include "ui_mydialog.h"
#include <mydialog.h>
#include <QColorDialog>

#include <ctime>
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
    srand(time(NULL));

    World *world = new World();

    world->add_scene(glm::vec3(-1,0, 0), 3, 0);
    world->add_scene(glm::vec3(-2,-5, -3), 3, 1);
    world->add_scene(glm::vec3(1,-5, 2), 5, 0);
    world->add_scene(glm::vec3(-5, -6, 0), 3, 0);

    QApplication a(argc, argv);

    MyDialog * win = new MyDialog(world);
    win->show();

    return a.exec();
}
